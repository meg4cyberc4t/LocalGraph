//
// Created by Igor Molchanov on 18.03.2022.
//
#include "vector"

class node {
public:
    explicit node(int value) {
        this->value = value;
    }

    int value;
    std::vector<std::pair<node*, int>> neighbors = {};

    void add_edge(node* place, int weight = 0){
        this->neighbors.emplace_back(place, weight);
    }
};
