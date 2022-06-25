#pragma once
#include "Coordinate.cpp"

template <class T>
struct Node {
        T data;
        Node* parent;
        int steps;

        Node();
        Node(T d);
        Node(T d, Node* p);
        Node(Node& node);
        virtual ~Node();
        void setData(T d);
        void incrementStep();
        void setNode(Node& node);
        T getData();
        int getSteps();
        void print();
        void printOne();
        int operator==(Node<T> const &m) const;
        int operator!=(Node<T> const &m) const;
        bool equals(Node<T>* node);
};

template <class T>
std::ostream &operator<<(std::ostream &os, Node<T> const &m) { 
    return os << m.data << " | steps: " << m.steps;
}