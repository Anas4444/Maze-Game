#pragma once
#include "StackFrontier.cpp"

template <class T>
class QueueFrontier : public StackFrontier<T> {
    public:
        QueueFrontier();
        virtual ~QueueFrontier();
        Node<Coordinate<T>>* remove();
};