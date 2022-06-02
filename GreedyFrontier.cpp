#include "GreedyFrontier.h"

template <class T>
GreedyFrontier<T>::GreedyFrontier() {
    this->rows = 6;
    this->colums = 10;
    this->destination = new Pair<T>(0, 8);
    this->fillhBoard();
}

template <class T>
GreedyFrontier<T>::GreedyFrontier(Pair<T>* dest, int rows, int colums) {
    this->destination = dest;
    this->rows = rows;
    this->colums = colums;
    this->fillhBoard();
}

template <class T>
GreedyFrontier<T>::~GreedyFrontier() {
    delete destination;
    for (int i=0; i<rows; i++) {
        delete[] hBoard[i];
    }
    delete[] hBoard;
}

template <class T>
void GreedyFrontier<T>::fillhBoard() {
    hBoard = new int*[rows];
    for (int i=0; i<rows; i++) hBoard[i] = new int[colums];
    for (int i=0; i<rows; i++) {
        for (int j=0; j<colums; j++) {
            hBoard[i][j] = heuricity(i, j, destination);
        }
    }
}

template <class T>
void GreedyFrontier<T>::printHBoard() {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<colums; j++) {
            std::cout << hBoard[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <class T>
int GreedyFrontier<T>::distance(Pair<T> p) {
    return this->hBoard[p.x][p.y];
}

template <class T>
int GreedyFrontier<T>::heuricity(int Ax, int Ay, Pair<T>* B) {
    //std::cout << "destination: " << *B << std::endl;
    int d1 = std::abs(Ay - B->y);
    int d2 = std::abs(Ax - B->x);
    if (d1 < d2) return d1 + std::abs(d1+Ax - B->x);
    return d2 + std::abs(d2+Ay - B->y);
}

template <class T>
Node<Pair<T>>* GreedyFrontier<T>::remove() {
    Node<Pair<T>>* p = new Node<Pair<T>>(*(StackFrontier<T>::frontier->at(0)));
    int f = 0;
    for (int i = 0; i<StackFrontier<T>::frontier->size(); i++) {
        Node<Pair<T>>* Bxy = StackFrontier<T>::frontier->at(i);
        Pair<T> xy = Bxy->getData();
        Pair<T> Pxy = p->getData();
        if (hBoard[Pxy.x][Pxy.y] > hBoard[xy.x][xy.y]) {
            p->setNode(*Bxy);
            f = i;
        }
    }
    StackFrontier<T>::frontier->erase(StackFrontier<T>::frontier->begin()+f);
    return p;
}