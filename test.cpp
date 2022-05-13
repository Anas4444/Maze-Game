//#include "Maze.cpp"
#include "NodeG.cpp"

int main() {
    /*Maze m("Maze/maze1.txt");
    m.print();
    m.alphaShortestPath(10000);
    //m.shortestPath();
    //m.search();
    m.showAll();*/
    NodeG* p0 = new NodeG();
    NodeG* p1 = new NodeG(Pair<int>(1, 2), p0);
    p1->addPoint(p0);
    p0->print();
    p1->print();
    
}