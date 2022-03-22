#include <iostream>
#include "graph.cpp"
#include "map"
#include "vector"

using namespace std;

template<typename T>
string graph_to_string(Graph<T> &graph) {
    string out;
    out += "{\n";
    for (const auto &item: graph.to_dictionary_of_adjacency()) {
        out += std::to_string(item.first) + ": ";
        out += "{";
        for (const auto &_item: item.second)
            out += std::to_string(_item.first) + ":" + std::to_string(_item.second) + ", ";
        out += "}, \n";
    }
    out += "}";
    return out;
}

int main() {
//    std::vector<string> nodes = {"v1", "v2", "v3", "v4", "v5", "v6"};
//    std::vector<std::vector<int>> raw = {
//            {0, 5, 0, 10, 0, 0},
//            {0, 0, 0, 0, 0, 11},
//            {15, 0, 0, 0, 2, 0},
//            {0, 2, 4, 0, 0, 0},
//            {0, 0, 0, 7, 0, 6},
//            {0, 0, 0, 4, 4, 0},
//    };
    map<char, map<char, int>> G = {
            {'A', {{'B', 5}, {'C', 15}, {'D', 10}}},
            {'B', {{'D', 2}, {'F', 11}}},
            {'C', {{'D', 4}, {'E', 6}}},
            {'D', {{'A', 3}, {'C', 3},  {'E', 5}, {'F', 4}}},
            {'E', {{'C', 2}, {'F', 6}}},
            {'F', {{'E', 2}}}
    };
    auto gr = Graph<char>(G);
//    for (const auto &item: gr.dijkstra(gr.nodes.front())) {
//        cout << item.first->value << '\t' << item.second << endl;
//    }
    auto path = gr.dijkstra_path(gr.find('A'), gr.find('E'));
    for (auto a: path) {
        cout << a->value << endl;
    }
}