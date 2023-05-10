#ifndef LISTE_H
#define LISTE_H
#include <iostream>
#include <cassert>


template <typename T>
struct Node
{
    T data;
    Node <T>* parent;
    Node <T>* next;
};

template <typename T>
class Liste
{
    private:
        Node <T>* head;
        int count;
        Node <T>* createNode(const T& value);
    
    public:
        Liste();
        ~Liste();
        void insert(const T& value);
        void insert(int pos, const T& value);
        void remove(T value);
        void remove(int pos);
        T& getNode(int pos) const;
        void print() const;
        int length() const;
};
#endif