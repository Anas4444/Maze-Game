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
        virtual Node<Pair<T>>* remove();
        void print();
};