#include "AStarFrontier.h"

template <class T>
AStarFrontier<T>::AStarFrontier(Pair<T>* dest, int rows, int colums) {
    this->rows = 6;
    this->colums = 10;
    this->destination = new Pair<T>(0, 8);
    this->fillhBoard();
}

template <class T>
void AStarFrontier<T>::add(Node<Pair<T>>* node) {
    if (node->parent) node->steps += node->parent->steps;
    StackFrontier<T>::frontier->push_back(node);
}

template <class T> 
Node<Pair<T>>* AStarFrontier<T>::remove() {
    Node<Pair<T>>* p = new Node<Pair<T>>(*(StackFrontier<T>::frontier->at(0)));
    int f = 0;
    for (int i = 0; i<StackFrontier<T>::frontier->size(); i++) {
        Node<Pair<T>>* Bxy = StackFrontier<T>::frontier->at(i);
        Pair<T> xy = Bxy->getData();
        Pair<T> Pxy = p->getData();
        if (GreedyFrontier<T>::hBoard[Pxy.x][Pxy.y]+p->getSteps() > GreedyFrontier<T>::hBoard[xy.x][xy.y]+Bxy->getSteps()) {
            p->setNode(*Bxy);
            f = i;
        }
    }
    StackFrontier<T>::frontier->erase(StackFrontier<T>::frontier->begin()+f);
    return p;
}