#pragma once
#include "Node.cpp"

template <class T>
class StackFrontier {
    protected:
        std::vector<Node<Coordinate<T>>*>* frontier;
    public:
        StackFrontier();
        virtual ~StackFrontier();
        virtual void add(Node<Coordinate<T>>* node);
        bool empty();
        bool inFrontier(Coordinate<T> Coordinate);
        virtual void replace(Node<Coordinate<T>>* node);
        Node<Coordinate<T>>* getNode(Node<Coordinate<T>>* node);
        virtual Node<Coordinate<T>>* remove();
        void del(Node<Coordinate<T>>* node);
        virtual int distance(Coordinate<T> p);
        virtual void printHBoard();
        void print();
        void printOne();
};