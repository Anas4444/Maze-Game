#include "GreedyFrontier.h"

template <class T>
GreedyFrontier<T>::GreedyFrontier() {
    this->dimensions = Coordinate<int>(10, 6);
    this->destination = new Coordinate<T>(0, 8);
    this->fillhBoard();
}

template <class T>
GreedyFrontier<T>::GreedyFrontier(Coordinate<int>* dest, Coordinate<int> dim) {
    this->destination = dest;
    this->dimensions = dim;
    this->fillhBoard();
}

template <class T>
GreedyFrontier<T>::~GreedyFrontier() {
    delete destination;
    for (int i=0; i<dimensions.y; i++) {
        delete[] hBoard[i];
    }
    delete[] hBoard;
}

template <class T>
void GreedyFrontier<T>::fillhBoard() {
    hBoard = new int*[dimensions.y];
    for (int i=0; i<dimensions.y; i++) hBoard[i] = new int[dimensions.x];
    for (int i=0; i<dimensions.y; i++) {
        for (int j=0; j<dimensions.x; j++) {
            hBoard[i][j] = heuricity4(Coordinate<int>(j, i), destination);
        }
    }
}

template <class T>
void GreedyFrontier<T>::printHBoard() {
    for (int i=0; i<dimensions.y; i++) {
        for (int j=0; j<dimensions.x; j++) {
            std::cout << hBoard[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <class T>
int GreedyFrontier<T>::distance(Coordinate<T> p) {
    return this->hBoard[p.y][p.x];
}

template <class T>
int GreedyFrontier<T>::heuricity8(Coordinate<int> A, Coordinate<int>* B) {
    //std::cout << "destination: " << *B << std::endl;
    int d1 = std::abs(A.y - B->y);
    int d2 = std::abs(A.x - B->x);
    if (d1 < d2) {
        if (A.x>B->x) return d1 + std::abs(A.x-d1 - B->x);
        return d1 + std::abs(d1+A.x - B->x);
    }
    if (A.y>B->y) return d2 + std::abs(A.y-d2 - B->y);
    return d2 + std::abs(d2+A.y - B->y);
}

template<class T>
int GreedyFrontier<T>::heuricity4(Coordinate<int> A, Coordinate<int>* B)
{
   return std::abs(A.y - B->y) + std::abs(A.x - B->x); 
}

template <class T>
Node<Coordinate<T>>* GreedyFrontier<T>::remove() {
    Node<Coordinate<T>>* p = new Node<Coordinate<T>>(*(StackFrontier<T>::frontier->at(0)));
    int f = 0;
    for (int i = 0; i<StackFrontier<T>::frontier->size(); i++) {
        Node<Coordinate<T>>* Bxy = StackFrontier<T>::frontier->at(i);
        Coordinate<T> xy = Bxy->getData();
        Coordinate<T> Pxy = p->getData();
        if (hBoard[Pxy.y][Pxy.x] > hBoard[xy.y][xy.x]) {
            p->setNode(*Bxy);
            f = i;
        }
    }
    StackFrontier<T>::frontier->erase(StackFrontier<T>::frontier->begin()+f);
    return p;
}