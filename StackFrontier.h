#pragma once
#include "Node.cpp"
#include <vector>

template <class T>
class StackFrontier {
    protected:
        std::vector<Node<Pair<T>>*>* frontier;
    public:
        StackFrontier();
        virtual ~StackFrontier();
        virtual void add(Node<Pair<T>>* node);
        bool empty();
        bool inFrontier(Node<Pair<T>>* node);
        virtual Node<Pair<T>>* remove();
        virtual int distance(Pair<T> p);
        virtual void printHBoard();
        void print();
        void printOne();
};