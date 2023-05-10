#pragma once
#include "stackFrontier.cpp"

template <class T, class V>
class Maze {
    private:
        std::vector<V> content;
        bool** walls;
        T start;
        T goal;
        int height, width;
        std::vector<T> explored;
        std::vector<Node<T, V>*> solution;
        int num_explored;

    public:
        Maze(std::string path); 
        bool ijInSolution(int i, int j);
        bool stateExplored(const T& state);
        void print();
        std::vector<std::tuple<V, T>> neighbors(const T& state);
        void solve();
};