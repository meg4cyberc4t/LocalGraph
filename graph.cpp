//
// Created by Igor Molchanov on 09.03.2022.
//
#include "iostream"
#include "map"
#include "vector"
#include "list"
#include "set"
#include "queue"

#include "graph.h"

#define CONTAINS(list, elem) (std::find(list.begin(), list.end(), elem) != list.end())

template<class T>
Graph<T>::Graph(std::map<T, std::list<T>> &adjacency_map) : adjacency_map(adjacency_map) {
}

template<class T>
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

template<class T>
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
std::list<T> Graph<T>::dfs() {
    return this->dfs(first());
}

template<typename T>
std::list<T> Graph<T>::dfs(T node) {
    std::list<T> visited_list = std::list<T>();
    std::list<T> ended_list = std::list<T>();
    this->dfs(node, &visited_list, &ended_list);
    return ended_list;
}

template<typename T>
void Graph<T>::dfs(T node, std::list<T> *visited_list, std::list<T> *ended_list) {
    if (CONTAINS((*visited_list), node) || CONTAINS((*ended_list), node)) {
        return;
    }
    visited_list->push_back(node);
    for (auto child: adjacency_map[node]) {
        this->dfs(child, visited_list, ended_list);
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

template<class T>
bool Graph<T>::bfs(T from, T to) {
    std::queue<T> queue = {};
    std::list<T> visited = {};
    queue.push(from);
    visited.push_back(from);
    while (queue.size() > 0) {
        T node = queue.back();
        queue.pop();
        for (T neighbour: this->adjacency_map[node]) {
            if (CONTAINS(visited, neighbour)) continue;
            if (neighbour == to) return true;
            queue.push(neighbour);
            visited.push_back(neighbour);
        }
    }
    return false;
}

template<class T>
std::map<T, T> Graph<T>::parents(T from, T to) {
    std::map<T, T> parents = {};
    std::queue<T> queue = {};
    std::list<T> visited = {};
    queue.push(from);
    while (queue.size() > 0) {
        T node = queue.back();
        queue.pop();
        visited.push_back(node);
        for (T neighbour: this->adjacency_map[node]) {
            if (CONTAINS(visited, neighbour)) continue;
            if (!parents.contains(neighbour)) parents[neighbour] = node;
            queue.push(neighbour);
        }
        if (node == to) return parents;
    }
    return parents;
}

template<class T>
std::list<T> Graph<T>::path_between(T from, T to) {
    std::map parents = this->parents(from, to);
    std::list<T> path = {};
    this->path_between(from, to, &path, &parents);
    return path;
}

template<class T>
void Graph<T>::path_between(T from, T to, std::list<T>* path, std::map<T, T>* parents) {
    path->push_front(to);
    if (from == to) return;
    path_between(from, parents->at(to), path, parents);
}


