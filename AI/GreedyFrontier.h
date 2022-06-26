#pragma once
#include "QueueFrontier.cpp"
#include <cmath>

template <class T>
class GreedyFrontier : public QueueFrontier<T> {
    protected:
        Coordinate<T>* destination;
        Coordinate<int> dimensions;
        int** hBoard;
    public:
        GreedyFrontier();
        GreedyFrontier(Coordinate<int>* dest, Coordinate<int> dim);
        virtual ~GreedyFrontier();
        int heuricity8(Coordinate<int> position, Coordinate<int>* destination);
        int heuricity4(Coordinate<int> position, Coordinate<int>* destination);
        void fillhBoard();
        void printHBoard();
        int distance(Coordinate<T> p);
        Node<Coordinate<T>>* remove();
};