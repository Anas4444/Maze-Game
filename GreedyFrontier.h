#pragma once
#include "QueueFrontier.cpp"
#include <cmath>

template <class T>
class GreedyFrontier : public QueueFrontier<T> {
    protected:
        Coordinate<T>* destination;
        int rows;
        int colums;
        int** hBoard;
    public:
        GreedyFrontier();
        GreedyFrontier(Coordinate<T>* dest, int rows, int colums);
        virtual ~GreedyFrontier();
        int heuricity(int Ax, int Ay, Coordinate<T>* B);
        void fillhBoard();
        void printHBoard();
        int distance(Coordinate<T> p);
        Node<Coordinate<T>>* remove();
};