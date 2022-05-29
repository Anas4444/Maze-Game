#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "Node.cpp"

template <class T, class V>
struct NodeS : public Node<T, V>
{
    NodeS<T, V>* parent;

    NodeS(const NodeS<T, V>& node) : Node(node.state, node.action) {
        this->parent = node.parent;
    }

    NodeS(T s, NodeS<T, V>* p, V a) : Node(s, a) {
        this->parent = p;
    }

    NodeS(T s, V a) : Node(s, a) {
        this->parent = nullptr;
    }

    NodeS(T s) : Node(s){
        this->parent = nullptr;
    }

    void setNode(T s, V a) {
        Node<T, V>::setNode(s, a);
        this->parent = nullptr;
    }

    void setNode(T s) {
        Node<T, V>::setNode(s);
        this->parent = nullptr;
    }
};

template <class T, class V>
class StackFrontier {
    public:
        std::vector<NodeS<T, V>>* frontier;
    public:
        StackFrontier();
        virtual ~StackFrontier();
        void add(const NodeS<T, V>& node);
        bool containsState(const T& state);
        bool empty();
        void show();
        virtual NodeS<T, V>* remove();
};

template <class T, class V>
class QueueFrontier : public StackFrontier<T, V> {
    public:
        NodeS<T, V>* remove();
};