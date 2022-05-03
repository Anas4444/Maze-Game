#pragma once
#include "GreedyFrontier.cpp"

template <class T>
class AStarFrontier : public GreedyFrontier<T> {
    public:
        AStarFrontier(Pair<T>* dest, int rows, int colums);
        void add(Node<Pair<T>>* node);
        Node<Pair<T>>* remove();
};