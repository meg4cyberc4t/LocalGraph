//
// Created by Igor Molchanov on 18.03.2022.
//

#include "iostream"
#include "node.cpp"
#include "list"
#include "map"
#include "queue"
#include "limits"

#define CONTAINS(list, elem) (std::find(list.begin(), list.end(), elem) != list.end())

template<class T>
class Graph {
public:
    Graph() = default;

    explicit Graph(const std::map<T, std::map<T, int>> &dictionary_of_adjacency) {
        for (const auto &item: dictionary_of_adjacency) {
            this->add_node(item.first);
        }
        for (const auto &item: dictionary_of_adjacency) {
            for (const auto &edge: item.second) {
                this->add_edge(item.first, edge.first, edge.second);
            }
        }
    }

    explicit Graph(std::vector<T> nodes, const std::vector<std::vector<int>> &adjacency_matrix) {
        for (const auto &item: nodes) {
            this->add_node(item);
        }
        for (int i = 0; i < adjacency_matrix.size(); ++i) {
            for (int j = 0; j < adjacency_matrix[i].size(); ++j) {
                if (adjacency_matrix[i][j] > 0) {
                    this->add_edge(nodes[i], nodes[j], adjacency_matrix[i][j]);
                }
            }
        }
    }


    explicit Graph(const std::map<T, std::list<T>> &dictionary_of_adjacency) {
        for (const auto &item: dictionary_of_adjacency) {
            this->add_node(item.first);
        }
        for (const auto &item: dictionary_of_adjacency) {
            for (const auto &edge: item.second) {
                this->add_edge(item.first, edge);
            }
        }
    }

    std::list<node<T> *> nodes = {};

    node<T>* add_node(T value) {
        auto new_node = new node<T>(value);
        this->nodes.push_back(new_node);
        return new_node;
    }

    node<T> *find(T value) {
        for (auto item: nodes) {
            if (item->value == value) return item;
        }
        return nullptr;
    }

    std::list<node<T>*> find_all(T value) {
        std::list<node<T>*> list = {};
        for (auto item: nodes) {
            if (item->value == value) list.push_back(item);
        }
        return list;
    }

    void add_edge(T start, T end, int weight = 0) {
        auto start_node = this->find(start);
        assert(start_node != nullptr);
        auto end_node = this->find(end);
        assert(end_node != nullptr);
        start_node->add_edge(end_node, weight);
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
        std::vector<node<T> *> list_black_nodes = {};
        std::vector<node<T> *> list_white_nodes = {};
        std::map<node<T> *, bool> need = {};
        need.insert({nodes.front(), false});
        while (!need.empty()) {
            node<T> *ptr = need.begin()->first;
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

    [[nodiscard]] int count() const {
        std::list<node<T> *> copy_nodes = nodes;
        int count = 0;
        while (!copy_nodes.empty()) {
            auto ptr = copy_nodes.front();
            for (const auto &item: ptr->dfs()) {
                copy_nodes.remove(item);
            }
            count++;
        }
        return count;
    }

    std::map<node<T> *, int> dijkstra(node<T> *start) {
        std::map<node<T> *, int> paths;
        std::queue<node<T> *> queue = {};
        for (const auto &item: this->nodes)
            paths[item] = std::numeric_limits<int>::max();
        paths[start] = 0;
        queue.push(start);
        while (!queue.empty()) {
            auto cur = queue.front();
            queue.pop();
            for (const auto &item: cur->neighbors) {
                auto p = paths[cur] + item.second;
                if (paths[item.first] > p) {
                    queue.push(item.first);
                    paths[item.first] = p;
                }
            }
        }
        return paths;
    }

    std::vector<node<T> *> dijkstra_path(node<T> *start, node<T> *end) {
        std::map<node<T> *, int> dij = dijkstra(start);
        std::vector<node<T> *> path = {};
        path.push_back(end);
        while (path.back() != start) {
            for (node<T> *item: this->nodes) {
                if (item->neighbors.contains(end) && dij[item] + item->neighbors.at(end) == dij[end]) {
                    path.push_back(item);
                    end = item;
                }
            }
        }
        return path;
    }
};
