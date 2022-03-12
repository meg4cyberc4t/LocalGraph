//
// Created by Igor Molchanov on 11.03.2022.
//
#pragma once

#ifndef LOCALGRAPH_GRAPH_H
#define LOCALGRAPH_GRAPH_H

#include "iostream"
#include "map"
#include "list"
#include "vector"
#include "set"

template<class T>
class Graph {
public:
    Graph() = default;

    explicit Graph(std::map <T, std::list<T>> &adjacency_map);

    static Graph from_nodes_edges_lists(std::vector <T> &nodes, std::vector <std::list<T>> &edges_lists);

    static Graph from_adjacency_matrix(std::vector <T> &nodes, std::vector <std::vector<int>> &adjacency_matrix);

    void add_node(T node);

    void add_edge(T node1, T node2);

    T first();
//
    void print();
//
    std::list <T> dfs();

    std::list <T> dfs(T node);

    std::list <T> nodes();

    int count();

    bool is_bipartite();

    bool bfs(T from, T to);

    std::map<T, T>  parents(T from, T to);

    std::list<T> path_between(T from, T to);

private:
    std::map <T, std::list<T>> adjacency_map = {};

    void dfs(T start_node, std::list <T> *visited_list, std::list <T> *ended_list);

    bool is_bipartite(T node, std::set <T> *list_white_nodes, std::set <T> *list_black_nodes, bool color);

    void path_between(T from, T to, std::list<T>* path, std::map<T, T>* parents);

};

#endif //LOCALGRAPH_GRAPH_H
