#pragma once
#include <iostream>
#include <tuple>
#include <vector>

template <class T, class V>
struct Node
{
    T state;
    V action;

    Node(const Node<T, V>& node) {
        this->state = node.state;
        this->action = node.action;
    }

    Node(T state, V action) {
        this->state = state;
        this->action = action;
    }

    Node(T state) {
        this->state = state;
        this->action = "";
    }

    void setNode(T state, V action) {
        this->state = state;
        this->action = action;
    }

    void showState() {
        std::cout << "[(" << std::get<0>(state) << ", " << std::get<1>(state) << "), ";
    }

    void showAction() {
        std::cout << action << "]" << std::endl;
    }
};

template <class T, class V>
class Maze {
    private:
        std::vector<V> content;
        bool** walls;
        int** checked;
        Node<T, V>* position;
        int height, width;
        int num_explored;

    public:
        Maze(std::string path); 
        bool allStatesChecked();
        void print();
        std::tuple<T, V> theBestNeighbor(const T& state);
        void solve();
};