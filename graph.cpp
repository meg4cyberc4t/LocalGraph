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

    T first();

    void print();

    std::list<T> passage_in_depth();
private:
    std::map<T, std::list<T>> adjacency_map = {};

    bool contains(std::list<T> *nodes, T node);
    void passage_in_depth(T start_node, std::list<T> *visited_list, std::list<T> *ended_list);
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
    if (contains(this->adjacency_map[node1], node2)) {
        this->adjacency_map[node1].push_back(node2);
    }
    if (contains(this->adjacency_map[node2], node1)) {
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

template<typename T>
T Graph<T>::first() {
    return this->adjacency_map.begin()->first;
}

template<typename T>
std::list<T> Graph<T>::passage_in_depth() {
    std::list<T> visited_list = std::list<T>();
    std::list<T> ended_list = std::list<T>();
    this->passage_in_depth(first(), &visited_list, &ended_list);
    return ended_list;
}


//T start_node = NULL,
template<typename T>
void Graph<T>::passage_in_depth(T node, std::list<T> *visited_list, std::list<T> *ended_list) {
    if (contains(visited_list, node) || contains(ended_list, node)){

        return;
    }
    visited_list->push_back(node);
    for (auto child: adjacency_map[node]) {
        this->passage_in_depth(child, visited_list, ended_list);
    }
    visited_list->remove(node);
    ended_list->push_back(node);
}

template<typename T>
bool Graph<T>::contains(std::list<T> *nodes, T node) {
    return (std::find(nodes->begin(), nodes->end(), node) !=
            nodes->end());
}

