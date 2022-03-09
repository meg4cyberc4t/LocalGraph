//
// Created by Igor Molchanov on 09.03.2022.
//
#include "iostream"

template<typename T>
class Graph{
public:
    Graph() = default;
    void check() {
        std::cout << typeid(T).name() << std::endl;
    }
};
