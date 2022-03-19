//
// Created by Igor Molchanov on 18.03.2022.
//

#include "iostream"
#include "node.cpp"
#include "list"
#include "map"
#include "queue"

#define CONTAINS(list, elem) (std::find(list.begin(), list.end(), elem) != list.end())

class Graph {
public:
    explicit Graph(const std::map<int, std::map<int, int>> &dictionary_of_adjacency) {
        for (const auto &item: dictionary_of_adjacency) {
            this->add_node(item.first);
        }
        for (const auto &item: dictionary_of_adjacency) {
            for (const auto &edge: item.second) {
                this->add_edge(item.first, edge.first, edge.second);
            }
        }
    }

    explicit Graph(const std::map<int, std::list<int>> &dictionary_of_adjacency) {
        for (const auto &item: dictionary_of_adjacency) {
            this->add_node(item.first);
        }
        for (const auto &item: dictionary_of_adjacency) {
            for (const auto &edge: item.second) {
                this->add_edge(item.first, edge);
            }
        }
    }

    std::list<node *> nodes = {};

    void add_node(int value) {
        node *new_node = new node(value);
        this->nodes.push_back(new_node);
    }

    node *find(int value) {
        for (node *item: nodes) {
            if (item->value == value) return item;
        }
        return nullptr;
    }

    void add_edge(int start, int end, int weight = 0) {
        auto start_node = this->find(start);
        assert(start_node != nullptr);
        auto end_node = this->find(end);
        assert(end_node != nullptr);
        start_node->add_edge(end_node, weight);
        end_node->add_edge(start_node, weight);
    }

    ~Graph() {
        for (const auto &item: this->nodes)
            delete item;
    }

    std::map<int, std::map<int, int>> to_dictionary_of_adjacency() {
        std::map<int, std::map<int, int>> result = {};
        for (const auto &item: this->nodes) {
            result[item->value] = {};
            for (const auto &neighbor: item->neighbors) {
                result[item->value][neighbor.first->value] = neighbor.second;
            }
        }
        return result;
    }

    bool is_twopartie() {
        std::vector<node *> list_black_nodes = {};
        std::vector<node *> list_white_nodes = {};
        std::map<node *, bool> need = {};
        need.insert({nodes.front(), false});
        while (!need.empty()) {
            node *ptr = need.begin()->first;
            bool color = need.begin()->second;
            need.erase(need.begin());
            if (CONTAINS(list_white_nodes, ptr)) {
                if (!color)
                    return false;
                continue;
            }
            if (CONTAINS(list_black_nodes, ptr)) {
                if (color)
                    return false;
                continue;
            }
        }
        return true;
    }
};
