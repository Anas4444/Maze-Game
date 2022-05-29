#include "stackFrontier.h"

template <class T, class V>
StackFrontier<T, V>::StackFrontier() {
    frontier = new std::vector<NodeS<T, V>>();
}

template <class T, class V>
StackFrontier<T, V>::~StackFrontier() {
    for (int i=0; i<frontier->size(); i++) {
        delete &frontier->at(i);
    }
    delete frontier;
}

template <class T, class V>
void StackFrontier<T, V>::add(const NodeS<T, V>& node) {
    frontier->push_back(node);
}

template <class T, class V>
bool StackFrontier<T, V>::containsState(const T& state) {
    for (int i=0; i<frontier->size(); i++) {
        if (frontier->at(i).state == state) return true;
    }
    return false;
}

template <class T, class V>
bool StackFrontier<T, V>::empty() {
    return frontier->size() == 0;
}

template <class T, class V>
NodeS<T, V>* StackFrontier<T, V>::remove() {
    NodeS<T, V>* node = new NodeS<T, V>(frontier->back());
    frontier->pop_back();
    return node; 
}

template<class T, class V>
void StackFrontier<T, V>::show() {
    for (int i=0; i<frontier.size(); i++) {
        frontier->at(i).showState();
        frontier->at(i).showAction();
    }
}

template<class T, class V>
NodeS<T, V>* QueueFrontier<T, V>::remove() {
    NodeS<T, V>* node = new NodeS<T, V>(StackFrontier<T, V>::frontier->at(0));
    StackFrontier<T, V>::frontier->erase(StackFrontier<T, V>::frontier->begin());
    return node;
}