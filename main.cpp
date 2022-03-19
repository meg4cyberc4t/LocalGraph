#include <iostream>
#include "graph.cpp"
#include "map"
using namespace std;

string graph_to_string(Graph& graph) {
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
//    map<int, list<int>> raw = {{1, {2, 4}},
//                                   {2, {1, 3}},
//                                   {3, {2, 4}},
//                                   {4, {1, 3}},
//                               {5, {}}
//    };
//    map<int, list<int>> raw = {{1, {2}},
//                               {2, {1}}};

    auto gr = Graph(raw);
//    cout << gr.nodes.size() << endl;
//    cout << graph_to_string(gr);
    cout << gr.is_twopartie() << endl;
    return 0;
}