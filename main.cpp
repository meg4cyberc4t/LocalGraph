#include "graph.cpp"

#define PRINT_LIST(list) \
std::cout << "[";        \
for (auto val : list) { std::cout << val; } \
std::cout << "]"  << std::endl;

#define PRINT_MAP(map) \
std::cout << "{";        \
for (auto const&[key, val]: map) { std::cout << key << ":" << val << " "; } \
std::cout << "}" << std::endl;

int main() {
//    std::list<char> nodes_list = {'A', 'B', 'C'};
//    std::list<std::list<int>> adjacency_matrix = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}};
//    Graph<char> a = Graph<char>(nodes_list, adjacency_matrix);

    std::map<char, std::list<char>> raw = {{'A', {'B', 'C'}},
                                           {'B', {'A'}},
                                           {'C', {'A'}}};
//    Graph<char> a = Graph<char>(raw);

//    std::vector<char> nodes = {'A', 'B', 'C'};
//    std::list<std::list<char>> edges_list = {{'A', 'B'},
//                                             {'B', 'C'}};
//    Graph<char> a = Graph<char>::from_nodes_edges_lists(nodes_list, edges_list);

//    std::vector<std::vector<int>> matrix = {
//            {0, 1, 1},
//            {1, 0, 0},
//            {1, 0, 0},
//    };
    Graph<char> a = Graph<char>(raw);
    a.print();
    for (auto alo:a.passage_in_depth()) {
        std::cout << alo;
    }
    return 0;
}