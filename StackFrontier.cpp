#include "StackFrontier.h"

template <class T>
StackFrontier<T>::StackFrontier() {
    this->frontier = new std::vector<Node<Pair<T>>*>();
}

template <class T>
StackFrontier<T>::~StackFrontier() {
    for (int i=0; i<frontier->size(); i++) delete frontier->at(i);
    delete frontier;
}

template <class T>
bool StackFrontier<T>::empty() {
    return this->frontier->size()==0;
}

template <class T>
void StackFrontier<T>::add(Node<Pair<T>>* node) {
    frontier->push_back(node);
}

template <class T>
Node<Pair<T>>* StackFrontier<T>::remove() {
    Node<Pair<T>>* p = new Node<Pair<T>>(*(frontier->at(frontier->size()-1)));
    frontier->erase(frontier->end()-1);
    return p;
}

template <class T>
void StackFrontier<T>::print() {
    for (int i=0; i<frontier->size(); i++) frontier->at(i)->print();
}