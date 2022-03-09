//
// Created by Igor Molchanov on 09.03.2022.
//
#include "iostream"
#include "map"
#include "vector"
#include "list"

template<typename T>
class Graph {
public:
    Graph() = default;

    explicit Graph(std::map<T, std::list<T>> &adjacency_map);

    static Graph from_nodes_edges_lists(std::vector<T> &nodes, std::vector<std::list<T>> &edges_lists);

    static Graph from_adjacency_matrix(std::vector<T> &nodes, std::vector<std::vector<int>> &adjacency_matrix);

    void add_node(T node);

    void add_edge(T node1, T node2);

    void print();

private:
    std::map<T, std::list<T>> adjacency_map = {};
};

template<typename T>
Graph<T>::Graph(std::map<T, std::list<T>> &adjacency_map) : adjacency_map(adjacency_map) {
}

template<typename T>
void Graph<T>::print() {
    std::cout << "Graph:\t{" << std::endl;
    for (auto const&[key, val]: adjacency_map) {
        std::cout << "\t" << key << ':';
        for (char child_node: val) {
            std::cout << (T) child_node << " ";
        }
        std::cout << "\t\t\t| " << val.size() << " size" << std::endl;
    }
    std::cout << "}" << std::endl;
}

template<typename T>
void Graph<T>::add_node(T node) {
    this->adjacency_map[node] = {};
}

template<typename T>
void Graph<T>::add_edge(T node1, T node2) {
    if (std::find(this->adjacency_map[node1].begin(), this->adjacency_map[node1].end(), node2) ==
        this->adjacency_map[node1].end()) {
        this->adjacency_map[node1].push_back(node2);
    }
    if (std::find(this->adjacency_map[node2].begin(), this->adjacency_map[node2].end(), node1) ==
        this->adjacency_map[node2].end()) {
        this->adjacency_map[node2].push_back(node1);
    }
}

template<typename T>
Graph<T> Graph<T>::from_nodes_edges_lists(std::vector<T> &nodes, std::vector<std::list<T>> &edges_lists) {
    Graph<T> graph = Graph<T>();
    for (T node: nodes)
        graph.add_node(node);
    for (std::list<T> edge: edges_lists)
        graph.add_edge(edge.front(), edge.back());
    return graph;
}

template<typename T>
Graph<T> Graph<T>::from_adjacency_matrix(std::vector<T> &nodes, std::vector<std::vector<int>> &adjacency_matrix) {
    Graph<T> graph = Graph<T>();
    for (T node: nodes)
        graph.add_node(node);
    for (int i = 0; i < adjacency_matrix.size(); ++i) {
        for (int j = 0; j < adjacency_matrix[i].size(); ++j) {
            if (adjacency_matrix[i][j] > 0) {
                graph.add_edge(nodes[i], nodes[j]);
            }
        }
    }
    return graph;
}