#pragma once
#include "StackFrontier.cpp"

template <class T>
class QueueFrontier : public StackFrontier<T> {
    public:
        Node<Coordinate<T>>* remove();
};