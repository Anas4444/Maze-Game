#pragma once
#include "QueueFrontier.cpp"
#include <cmath>

template <class T>
class GreedyFrontier : public QueueFrontier<T> {
    protected:
        Pair<T>* destination;
        int rows;
        int colums;
        int** hBoard;
    public:
        GreedyFrontier();
        GreedyFrontier(Pair<T>* dest, int rows, int colums);
        ~GreedyFrontier();
        int heuricity(int Ax, int Ay, Pair<T>* B);
        void fillhBoard();
        void printHBoard();
        int distance(Pair<T> p);
        Node<Pair<T>>* remove();
};