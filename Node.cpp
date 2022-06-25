#include "Node.h"

template <class T>
Node<T>::Node() {
    this->data = Coordinate<int>();
    this->parent = nullptr;
    this->steps = 0;
}

template <class T>
Node<T>::Node(T d) {
    this->data = d;
    this->parent = nullptr;
    this->steps = 0;
}

template <class T>
Node<T>::Node(T d, Node<T>* p) {
    this->data = d;
    this->parent = p;
    this->steps = 0;
}

template <class T>
Node<T>::Node(Node& node) {
    this->data = node.data;
    this->parent = node.parent;
    this->steps = node.steps;
}

template <class T>
Node<T>::~Node() {
    Node<T>* p = this->parent;
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
    std::cout << this->data << " steps : " << this->steps;
}

template <class T>
bool Node<T>::equals(Node<T>* node) {
    Node<T>* p1 = this;
    Node<T>* p2 = node;
    while (p1!=nullptr && p2!=nullptr) {
        if (p1->getData()!=p2->getData()) return 0;
        p1 = p1->parent;
        p2 = p2->parent;
    }
    if (p1==p2)
        return 1;
    return 0;
}

template <class T>
int Node<T>::operator==(Node<T> const &m) const { 
    return (data==m.data);
}