#include "graph.cpp"

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
    return 0;
}