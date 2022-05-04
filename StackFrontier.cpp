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
bool StackFrontier<T>::inFrontier(Node<Pair<T>>* node) {
    for (int i=0; i<this->frontier->size(); i++) {
        if (node->getData()==this->frontier->at(i)->getData()) return true;
    }
    return false;
}

template <class T>
int StackFrontier<T>::distance(Pair<T> p) { return 0; }

template <class T>
void StackFrontier<T>::printHBoard() {}

template <class T>
void StackFrontier<T>::print() {
    for (int i=0; i<frontier->size(); i++) frontier->at(i)->print();
}

template <class T>
void StackFrontier<T>::printOne() {
    for (int i=0; i<frontier->size(); i++) {
        frontier->at(i)->printOne();
        std::cout << " | distance : " << distance(frontier->at(i)->getData()) << std::endl;
    }
    std::cout << "\n";
}