#include "Node.h"

template <class T>
Node<T>::Node() {
    this->data = Pair<int>();
    this->parent = nullptr;
    this->steps = 1;
}

template <class T>
Node<T>::Node(T d) {
    this->data = d;
    this->parent = nullptr;
    this->steps = 1;
}

template <class T>
Node<T>::Node(T d, Node<T>* p) {
    this->data = d;
    this->parent = p;
    this->steps = 1;
}

template <class T>
Node<T>::Node(Node& node) {
    this->data = node.data;
    this->parent = node.parent;
    this->steps = node.steps;
}

template <class T>
Node<T>::~Node() {
    Node<T>* p = this;
    while(p != nullptr) {
        Node<T>* del = p;
        p = p->parent;
        delete del;
    }
}

template <class T>
void Node<T>::setData(T d) {
    this->data = d;
}

template <class T>
void Node<T>::incrementStep() {
    this->steps++;
}

template <class T>
void Node<T>::setNode(Node& node) {
    this->data = node.data;
    this->parent = node.parent;
    this->steps = node.steps;
}

template <class T>
T Node<T>::getData() {
    return this->data;
}

template <class T>
int Node<T>::getSteps() {
    return this->steps;
}

template<class T>
void Node<T>::print() {
    Node* p = this;
    while (p != nullptr) {
        std::cout << p->data << " steps : " << p->steps << std::endl;
        p = p->parent;
    }
}

template<class T>
void Node<T>::printOne() {
    std::cout << this->data << " steps : " << this->steps << std::endl;
}