#include "NodeG.h"

NodeG::NodeG() {
    this->data.time = 0;
    this->points = new std::vector<NodeG*>();
    this->parent = nullptr;
    this->next = nullptr;
    this->steps = 0;
}

NodeG::NodeG(Pair<int> pos) {
    this->position = pos;
    this->data.time = 0;
    this->points = new std::vector<NodeG*>();
    this->parent = nullptr;
    this->next = nullptr;
    this->steps = 0;
}

NodeG::NodeG(Pair<int> pos, NodeG* p) {
    this->position = pos;
    this->points = new std::vector<NodeG*>();
    addPt(p);
    this->parent = p;
    this->next = nullptr;
    this->steps = 0;
}

NodeG::NodeG(Data d, Pair<int> pos) {
    this->data = d;
    this->position = pos;
    this->points = new std::vector<NodeG*>();
    this->parent = nullptr;
    this->next = nullptr;
    this->steps = 0;
}

NodeG::NodeG(Data d, Pair<int> pos, std::vector<NodeG*>* p) {
    this->data = d;
    this->position = pos;
    this->points = new std::vector<NodeG*>();
    for (int i=0; i<p->size(); i++) {
        this->points->push_back(p->at(i));
    }
    this->parent = p->at(0);
    this->next = nullptr;
    this->steps = 0;
}

NodeG::NodeG(Data d, Pair<int> pos, NodeG* p) {
    this->data = d;
    this->position = pos;
    this->points = new std::vector<NodeG*>();
    this->points->push_back(p);
    this->parent = p;
    this->next = nullptr;
    this->steps = 0;
}

NodeG::NodeG(NodeG& node) {
    this->data = node.data;
    this->points = node.points;
    this->fullpt = node.fullpt;
    this->parent = node.parent;
    this->next = node.next;
    this->steps = node.steps;
}

void NodeG::setPoints(std::vector<NodeG*>* p) {
    this->points->clear();
    for (int i=0; i<p->size(); i++) {
        this->points->push_back(p->at(i));
        this->fullpt.push_back(p->at(i));
    }
}

void NodeG::setNext(NodeG* p) {
    this->next = p;
}

void NodeG::addPoint(NodeG* pt) {
    this->points->push_back(pt);
}

void NodeG::addPt(NodeG* node) {
    if (inVector(node, this->fullpt)) return;
    this->fullpt.push_back(node);
}

bool NodeG::inVector(NodeG* node, std::vector<NodeG*> vec) {
    for (int i=0; i<vec.size(); i++) {
        if (node->position==vec[i]->position) return true;
    }
    return false;
}

void NodeG::setData(Data d) {
    this->data = d;
}

void NodeG::print() {
    std::cout << this->data << std::endl;
    for (int i=0; i<this->points->size(); i++) {
        std::cout << "p" << i << ": " << this->points->at(i)->data;
        if (i!=this->points->size()-1) std::cout << " | ";
    }
    std::cout << "\n";
}