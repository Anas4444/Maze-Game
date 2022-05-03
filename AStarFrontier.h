#pragma once
#include "GreedyFrontier.cpp"

template <class T>
class AStarFrontier : public GreedyFrontier<T> {
    public:
        void add(Node<Pair<T>>* node);
        Node<Pair<T>>* remove();
};