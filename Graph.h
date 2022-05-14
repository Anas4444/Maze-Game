#pragma once
#include "NodeG.cpp"

class Graph {
    private:
        std::vector<NodeG*> section;
        std::vector<NodeG*> isolated;
        NodeG* graph;
    public:
        Graph();
        Graph(int **board, Pair<int> dimensions);
        Graph(Graph& g);
        virtual ~Graph();
        std::vector<NodeG*> neighbours(NodeG* node, int** board, Pair<int> d);
        bool inVector(NodeG* node, std::vector<NodeG*> tempS);
        void print();
};