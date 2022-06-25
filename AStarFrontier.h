#pragma once
#include "GreedyFrontier.cpp"

template <class T>
class AStarFrontier : public GreedyFrontier<T> {
    protected:
        bool priorityD = false;
    public:
        AStarFrontier(Coordinate<T>* dest, int rows, int colums);
        void setPriority(bool priority);
        bool getPriority();
        void add(Node<Coordinate<T>>* node);
        void replace(Node<Coordinate<T>>* node);
        Node<Coordinate<T>>* remove();
};