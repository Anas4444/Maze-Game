#pragma once
#include "GreedyFrontier.cpp"

template <class T>
class AStarFrontier : public GreedyFrontier<T> {
    protected:
        bool priorityD = false;
    public:
        AStarFrontier(Pair<T>* dest, int rows, int colums);
        void setPriority(bool priority);
        bool getPriority();
        void add(Node<Pair<T>>* node);
        void replace(Node<Pair<T>>* node);
        Node<Pair<T>>* remove();
};