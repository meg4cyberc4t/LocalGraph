#include <iostream>
#include "graph.cpp"

using namespace std;

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
    auto gr = Graph();
    gr.add_node(4);
    gr.add_node(5);
    gr.add_node(6);
    gr.add_edge(4, 5);
    gr.add_edge(4, 6);
    cout << gr.nodes.size() << endl;
    cout << graph_to_string(gr);
    return 0;
}