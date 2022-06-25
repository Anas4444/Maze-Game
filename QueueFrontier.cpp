#include "QueueFrontier.h"

template <class T>
Node<Coordinate<T>>* QueueFrontier<T>::remove() {
    Node<Coordinate<T>>* p = new Node<Coordinate<T>>(*(StackFrontier<T>::frontier->at(0)));
    StackFrontier<T>::frontier->erase(StackFrontier<T>::frontier->begin());
    return p;
}