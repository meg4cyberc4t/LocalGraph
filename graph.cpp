//
// Created by Igor Molchanov on 09.03.2022.
//
#include "iostream"
#include "map"
#include "vector"
#include "list"
#include "set"

#define CONTAINS(list, elem) (std::find(list.begin(), list.end(), elem) != list.end())

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

    std::list<T> passage_in_depth(T node);

    std::list<T> nodes();

    int count();

    bool is_bipartite();


// TODO: Обход в ширину

private:
    std::map<T, std::list<T>> adjacency_map = {};

    void passage_in_depth(T start_node, std::list<T> *visited_list, std::list<T> *ended_list);

    bool is_bipartite(T node, std::set<T> *list_white_nodes, std::set<T> *list_black_nodes, bool color);
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
    if (CONTAINS(this->adjacency_map[node1], node2)) {
        this->adjacency_map[node1].push_back(node2);
    }
    if (CONTAINS(this->adjacency_map[node2], node1)) {
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
    return this->passage_in_depth(first());
}

template<typename T>
std::list<T> Graph<T>::passage_in_depth(T node) {
    std::list<T> visited_list = std::list<T>();
    std::list<T> ended_list = std::list<T>();
    this->passage_in_depth(node, &visited_list, &ended_list);
    return ended_list;
}

template<typename T>
void Graph<T>::passage_in_depth(T node, std::list<T> *visited_list, std::list<T> *ended_list) {
    if (CONTAINS((*visited_list), node) || CONTAINS((*ended_list), node)) {
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
std::list<T> Graph<T>::nodes() {
    std::list<T> nodes;
    for (auto const &imap: adjacency_map)
        nodes.push_back(imap.first);
    return nodes;
}

template<typename T>
int Graph<T>::count() {
    int count = 0;
    std::list<T> nodes = this->nodes();
    while (!nodes.empty()) {
        T node = nodes.front();
        std::list<T> components = this->passage_in_depth(node);
        for (auto component: components) {
            nodes.remove(component);
        }
        ++count;
    }
    return count;
}

template<typename T>
bool Graph<T>::is_bipartite() {
    std::set<T> list_white_nodes = std::set<T>();
    std::set<T> list_black_nodes = std::set<T>();
    return this->is_bipartite(first(), &list_white_nodes, &list_black_nodes, false);
}

template<typename T>
bool Graph<T>::is_bipartite(T node, std::set<T> *list_white_nodes, std::set<T> *list_black_nodes, bool color) {
    if (CONTAINS((*list_black_nodes), node)) {
        return !color;
    }
    if (CONTAINS((*list_white_nodes), node)) {
        return color;
    }
    if (color) {
        list_white_nodes->insert(node);
    } else {
        list_black_nodes->insert(node);
    }
    for (auto n: this->adjacency_map[node]) {
        bool value = this->is_bipartite(n, list_white_nodes, list_black_nodes, !color);
        if (!value) {
            return false;
        }
    }
    return true;
}