#pragma once

template <class T, class V>
struct Node
{
    T state;
    V action;

    Node(const Node<T, V>& node);

    Node(T s, V a);

    Node(T s);

    void setNode(T s, V a);

    void setNode(T s);

    void showState();

    void showAction();
};