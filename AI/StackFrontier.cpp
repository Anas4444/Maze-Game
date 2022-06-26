#include "StackFrontier.h"

template <class T>
StackFrontier<T>::StackFrontier() {
    this->frontier = new std::vector<Node<Coordinate<T>>*>();
}

template <class T>
StackFrontier<T>::~StackFrontier() {
    //for (int i=0; i<frontier->size(); i++) delete frontier->at(i);
    frontier->clear();
    delete frontier;
}

template <class T>
bool StackFrontier<T>::empty() {
    return this->frontier->size()==0;
}

template <class T>
void StackFrontier<T>::add(Node<Coordinate<T>>* node) {
    frontier->push_back(node);
}

template <class T>
Node<Coordinate<T>>* StackFrontier<T>::remove() {
    Node<Coordinate<T>>* p = new Node<Coordinate<T>>(*(frontier->at(frontier->size()-1)));
    frontier->erase(frontier->end()-1);
    return p;
}

template <class T>
void StackFrontier<T>::del(Node<Coordinate<T>>* node) {
    for (int i=0; i<frontier->size(); i++) {
        if (node->getData()==frontier->at(i)->getData()) {
            frontier->erase(frontier->begin()+i);
            break;
        }
    }
}

template <class T>
void StackFrontier<T>::replace(Node<Coordinate<T>>* node) {
    del(node);
    this->frontier->push_back(node);
}

template <class T>
Node<Coordinate<T>>* StackFrontier<T>::getNode(Node<Coordinate<T>>* node) {
    for (int i=0; i<this->frontier->size(); i++) {
        if (this->frontier->at(i)->getData()==node->getData()) return this->frontier->at(i);
    }
}

template <class T>
bool StackFrontier<T>::inFrontier(Coordinate<T> p) {
    for (int i=0; i<this->frontier->size(); i++) {
        if (p==this->frontier->at(i)->getData()) return true;
    }
    return false;
}

template <class T>
int StackFrontier<T>::distance(Coordinate<T> p) { return 0; }

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