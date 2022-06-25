#pragma once
#include "Data.cpp"
#include "Node.cpp"

struct NodeG {
        Data data;
        Coordinate<int> position;
        std::vector<NodeG*>* points;
        std::vector<NodeG*> fullpt;
        NodeG* parent;
        NodeG* next;
        int steps;

        NodeG();
        NodeG(Coordinate<int> pos);
        NodeG(Coordinate<int> pos, NodeG* p);
        NodeG(Data d, Coordinate<int> pos);
        NodeG(Data d, Coordinate<int> pos, std::vector<NodeG*>* p);
        NodeG(Data d, Coordinate<int> pos, NodeG* p);
        NodeG(NodeG& node);
        void setPoints(std::vector<NodeG*>* p);
        void setNext(NodeG* p);
        void addPoint(NodeG* pt);
        void addPt(NodeG* node);
        void setData(Data d);
        void print();
        bool inVector(NodeG* node, std::vector<NodeG*> vec);
};