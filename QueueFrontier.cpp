#include "QueueFrontier.h"

template <class T>
Node<Pair<T>>* QueueFrontier<T>::remove() {
    Node<Pair<T>>* p = new Node<Pair<T>>(*(StackFrontier<T>::frontier->at(0)));
    StackFrontier<T>::frontier->erase(StackFrontier<T>::frontier->begin());
    return p;
}