#include <iostream>
#include <array>
#include "graph.cpp"
#include "map"
#include "set"
#include "vector"

using namespace std;

template<typename T>
string graph_to_string(Graph<T> &graph) {
    string out;
    out += "{\n";
    for (const auto &item: graph.to_dictionary_of_adjacency()) {
        out += std::to_string(item.first) + ": ";
        out += "{";
        for (const auto &_item: item.second)
            out += std::to_string(_item.first) + ":" + std::to_string(_item.second) + ", ";
        out += "}, \n";
    }
    out += "}";
    return out;
}


int main() {
//    std::vector<string> nodes = {"v1", "v2", "v3", "v4", "v5", "v6"};
//    std::vector<std::vector<int>> raw = {
//            {0, 5, 0, 10, 0, 0},
//            {0, 0, 0, 0, 0, 11},
//            {15, 0, 0, 0, 2, 0},
//            {0, 2, 4, 0, 0, 0},
//            {0, 0, 0, 7, 0, 6},
//            {0, 0, 0, 4, 4, 0},
//    };

//    int N, M;
//    cin >> N >> M;
    const int N = 4;
    const int M = 5;

    std::vector<std::vector<int>> input = {
            {0, 0, 0, 0, 1},
            {0, 1, 1, 0, 2},
            {0, 2, 1, 0, 0},
            {0, 0, 1, 0, 0}
    };

    std::array<std::array<node<int> *, M>, N> local_matrix_ptrs = std::array<std::array<node<int> *, M>, N>();

    auto graph = Graph<int>();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
//            int check;
//            cin >> check;
            int check = input[i][j];
            local_matrix_ptrs[i][j] = graph.add_node(check);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (local_matrix_ptrs[i][j]->value == 1) continue;

            node<int> *node;

            /// Поиск верхнего соседа
            if (i != 0) {
                for (int l = i; l > 0; l--) {
                    if (local_matrix_ptrs[l - 1][j]->value == 1) break;
                    node = local_matrix_ptrs[l - 1][j];
                }
                local_matrix_ptrs[i][j]->add_edge(node);
            }
            ///

            /// Поиск нижнего соседа
            if (i != N) {
                for (int l = i; l < N - 1; l++) {
                    if (local_matrix_ptrs[l + 1][j]->value == 1) break;
                    node = local_matrix_ptrs[l + 1][j];
                }
                local_matrix_ptrs[i][j]->add_edge(node);
            }
            ///

            /// Поиск левого соседа
            if (j != 0) {
                for (int l = j; l > 0; l--) {
                    if (local_matrix_ptrs[i][l - 1]->value == 1) break;
                    node = local_matrix_ptrs[i][l - 1];
                }
                local_matrix_ptrs[i][j]->add_edge(node);
            }
            ///

            /// Поиск правого соседа
            if (j != M) {
                for (int l = j; l < M - 1; l++) {
                    if (local_matrix_ptrs[i][l + 1]->value == 1) break;
                    node = local_matrix_ptrs[i][l + 1];
                }
                local_matrix_ptrs[i][j]->add_edge(node);
            }
            ///
        }
    }

    std::set<unsigned long long> results = {};
    for (node<int> *end: graph.find_all(2)) {
        results.insert(graph.dijkstra_path(local_matrix_ptrs[3][0], end).size() - 1);
    }
    cout << results.begin().operator*();
}