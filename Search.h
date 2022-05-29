#pragma once
#include <iostream>
#include "stackFrontier.cpp"

template <class T, class V>
class Maze {
    public:
        std::vector<V> content;
        int** explored;
        NodeS<T, V>* start;
        NodeS<T, V>* goal;
        int height, width;
        std::vector<NodeS<T, V>*> solution;
        int num_explored;

    public:
        Maze(std::string path); 
        bool ijInSolution(int i, int j);
        bool stateExplored(const T& state);
        bool allStatesExplored();
        std::vector<std::tuple<T, V>> Neighbors(const T& state);
        std::tuple<T, V> theBestNeighbor(const T& state);
        void reset(NodeS<T, V>& finalDestination);
        void checkAll();
        void solve();
        void print();
};