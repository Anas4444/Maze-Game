#include "Node.h"

template<class T, class V>
Node<T, V>::Node(const Node<T, V>& node)
{
    this->state = node.state;
    this->action = node.action;
}

template<class T, class V>
Node<T, V>::Node(T s, V a)
{
    this->state = s;
    this->action = a;
}

template<class T, class V>
Node<T, V>::Node(T s)
{
    this->state = s;
    this->action = "";
}

template<class T, class V>
void Node<T, V>::setNode(T s, V a)
{
    this->state = s;
    this->action = a;
}

template<class T, class V>
void Node<T, V>::setNode(T s)
{
    this->state = s;
    this->action = "";
}

template<class T, class V>
void Node<T, V>::showState()
{
    std::cout << "[(" << std::get<0>(state) << ", " << std::get<1>(state) << "), ";
}

template<class T, class V>
void Node<T, V>::showAction()
{
    std::cout << action << "]" << std::endl;
}
