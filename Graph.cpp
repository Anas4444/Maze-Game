#include "Graph.h"

Graph::Graph() {

}

Graph::Graph(int **board, Pair<int> d) {
    std::vector<std::vector<NodeG*>> nghbSection;
    for (int i=0; i<d.x; i++) {
        for (int j=0; j<d.y; j++) {
            if (board[i][j]<0) continue;
            NodeG* node = new NodeG(Pair<int>(i, j));
            std::vector<NodeG*> neighb = neighbours(node, board, d);
            std::vector<NodeG*> nghb;
            if (neighb.size()>=3) {
                section.push_back(new NodeG(Data(1), Pair<int>(i, j)));
                for (int k=0; k<neighb.size(); k++) {
                    nghb.push_back(neighb[k]);
                }
                nghbSection.push_back(nghb);
            }
        }
    }
    std::vector<NodeG*> tempS;
    for (int i=0; i<section.size(); i++) {
        tempS.push_back(new NodeG(*section[i]));
    }
    for (int i=0; i<section.size(); i++) {
        for (int j=0; j<nghbSection[i].size(); j++) {
            NodeG* node = nghbSection[i][j];
            std::vector<NodeG*> ngh = neighbours(node, board, d);
            int distance = 0;
            int n = ngh.size();
            while (n<3 && n>1) {
                for (int k=0; k<n; k++) {
                    NodeG* previous = node->parent;
                    if (ngh[k]->position==previous->position) ngh.erase(ngh.begin()+k);
                }
                node = ngh[0];
                distance++;
                ngh = neighbours(node, board, d);
                n = ngh.size();
            }
            if (!inSection(node, tempS)) continue;
            NodeG* p;
            if (n>1)
            {
                p = node->parent;   
                p->addPoint(node);
                node->addPoint(p);
            }
            else p = node;
            p->addPoint(section[i]);
            p->setData(Data(distance));
            section[i]->addPoint(p);
        }
        tempS.erase(tempS.begin());
    }
}

bool Graph::inSection(NodeG* node, std::vector<NodeG*> tempS) {
    for (int i=0; i<tempS.size(); i++) {
        if (node->position==tempS[i]->position) return true;
    }
    return false;
}

std::vector<NodeG*> Graph::neighbours(NodeG* node, int** board, Pair<int> d) {
    Pair<int> pos = node->position;
    Pair<int> nghb[4] {Pair<int>(pos.x+1, pos.y), Pair<int>(pos.x-1, pos.y),
                       Pair<int>(pos.x, pos.y+1), Pair<int>(pos.x, pos.y-1)}; 
    std::vector<NodeG*> result;
    for (int i=0; i<4; i++) {
        if (nghb[i].x < d.x && nghb[i].y < d.y && nghb[i].x >= 0 && nghb[i].y >= 0 && board[nghb[i].x][nghb[i].y]!=-1)
            result.push_back(new NodeG(nghb[i], node));
    }
    return result;
}