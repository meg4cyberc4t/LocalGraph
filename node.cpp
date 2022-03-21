//
// Created by Igor Molchanov on 18.03.2022.
//
#include "vector"
#include "list"
#include "queue"

#define CONTAINS(list, elem) (std::find(list.begin(), list.end(), elem) != list.end())

struct node {
public:
    explicit node(int value) {
        this->value = value;
    }

    int value;
    std::vector<std::pair<node *, int>> neighbors = {};

    void add_edge(node *place, int weight = 0) {
        this->neighbors.emplace_back(place, weight);
    }

    std::list<node *> dfs() {
        std::list<node *> blacks = {};
        std::list<node *> grays = {};
        std::queue<node *> queue = {};
        queue.push(this);
        while (!queue.empty()) {
            node *ptr = queue.front();
            if (CONTAINS(grays, ptr)) {
                grays.remove(ptr);
                blacks.push_back(ptr);
                queue.pop();
            } else if (CONTAINS(blacks, ptr)) {
                queue.pop();
            } else {
                grays.push_back(ptr);
                for (const auto &item: ptr->neighbors) {
                    queue.push(item.first);
                }
            }
        }
        return blacks;
    }

    bool bfs(node *to) {
        std::list<node *> visited = {};
        std::queue<node *> queue = {};
        queue.push(this);
        visited.push_back(this);
        while (!queue.empty()) {
            node *ptr = queue.front();
            if (ptr == to) {
                return true;
            } else {
                auto local_neighbors = ptr->neighbors;
                queue.pop();
                for (const auto &item: local_neighbors) {
                    if (CONTAINS(visited, item.first)) continue;
                    queue.push(item.first);
                    visited.push_back(item.first);
                }
            }
        }
        return false;
    }
};
