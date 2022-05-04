#pragma once
#include "GreedyFrontier.cpp"

template <class T>
class AStarFrontier : public GreedyFrontier<T> {
    protected:
        bool distance = false;
    public:
        AStarFrontier(Pair<T>* dest, int rows, int colums);
        void setPriority(bool d);
        bool getPriority();
        void add(Node<Pair<T>>* node);
        Node<Pair<T>>* remove();
};