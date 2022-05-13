#pragma once
#include "Data.cpp"
#include "Pair.cpp"

struct NodeG {
        Data data;
        Pair<int> position;
        std::vector<NodeG*>* points;
        NodeG* parent;
        int steps;

        NodeG();
        NodeG(Pair<int> pos);
        NodeG(Pair<int> pos, NodeG* p);
        NodeG(Data d, Pair<int> pos);
        NodeG(Data d, Pair<int> pos, std::vector<NodeG*>* p);
        NodeG(Data d, Pair<int> pos, NodeG* p);
        NodeG(NodeG& node);
        void setPoints(std::vector<NodeG*>* p);
        void addPoint(NodeG* pt);
        void setData(Data d);
        void print();
};