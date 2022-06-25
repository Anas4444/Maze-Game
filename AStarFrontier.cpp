#include "AStarFrontier.h"

template <class T>
AStarFrontier<T>::AStarFrontier(Coordinate<T>* dest, int rows, int colums) {
    this->rows = rows;
    this->colums = colums;
    this->destination = new Coordinate<T>(*dest);
    this->fillhBoard();
}

template <class T>
void AStarFrontier<T>::setPriority(bool priority) {
    this->priorityD = priority;
}

template <class T>
bool AStarFrontier<T>::getPriority() {
    return this->priorityD;
}

template <class T>
void AStarFrontier<T>::add(Node<Coordinate<T>>* node) {
    if (node->parent) node->steps += node->parent->steps + 1;
    StackFrontier<T>::frontier->push_back(node);
}

template <class T>
void AStarFrontier<T>::replace(Node<Coordinate<T>>* node) {
    StackFrontier<T>::del(node);
    if (node->parent) node->steps += node->parent->steps + 1;
    StackFrontier<T>::frontier->push_back(node);
}

template <class T> 
Node<Coordinate<T>>* AStarFrontier<T>::remove() {
    Node<Coordinate<T>>* p = new Node<Coordinate<T>>(*(StackFrontier<T>::frontier->at(0)));
    int f = 0;
    for (int i = 0; i<StackFrontier<T>::frontier->size(); i++) {
        Node<Coordinate<T>>* Bxy = StackFrontier<T>::frontier->at(i);
        Coordinate<T> xy = Bxy->getData();
        Coordinate<T> Pxy = p->getData();
        if (GreedyFrontier<T>::hBoard[Pxy.x][Pxy.y]+p->getSteps() > GreedyFrontier<T>::hBoard[xy.x][xy.y]+Bxy->getSteps()) {
            p->setNode(*Bxy);
            f = i;
        }
        else if (GreedyFrontier<T>::hBoard[Pxy.x][Pxy.y]+p->getSteps() == GreedyFrontier<T>::hBoard[xy.x][xy.y]+Bxy->getSteps()) {
            if (this->priorityD)
                if (p->getSteps() > Bxy->getSteps()) {
                    p->setNode(*Bxy);
                    f = i;
                }
            else {
                if (GreedyFrontier<T>::hBoard[Pxy.x][Pxy.y] > GreedyFrontier<T>::hBoard[xy.x][xy.y]) {
                    p->setNode(*Bxy);
                    f = i;
                }
            }
        }
    }
    StackFrontier<T>::frontier->erase(StackFrontier<T>::frontier->begin()+f);
    return p;
}