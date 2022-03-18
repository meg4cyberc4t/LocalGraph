#include <iostream>
#include "graph.cpp"

using namespace std;

int main() {
    auto gr = Graph();

    gr.add_node(4);
    gr.add_node(5);
    gr.add_edge(4, 5);
    cout << gr.nodes.size() << endl;


    gr.dispose();
    return 0;
}
