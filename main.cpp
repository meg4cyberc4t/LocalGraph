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
    map<int, map<int, int>> raw = {{1, {{2,0}, {3,0}}},
                                   {2, {{1, 0}, {3, 0}}},
                                   {3, {{1, 0}, {2, 0}}}};

    auto gr = Graph(raw);
    cout << gr.nodes.size() << endl;
    cout << graph_to_string(gr);
    return 0;
}