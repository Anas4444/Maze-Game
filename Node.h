#pragma once
#include "Pair.cpp"

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
};