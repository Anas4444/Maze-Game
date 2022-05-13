#include "Maze.cpp"
//#include "NodeG.cpp"

int main() {
    Maze m("Maze/maze2.txt");
    m.print();
    m.alphaShortestPath(2);
    //m.shortestPath();
    //m.search();
    m.showAll();
    /*NodeG* p0 = new NodeG();
    NodeG* p1 = new NodeG(Pair<int>(1, 2), p0);
    p1->addPoint(p0);
    p0->print();
    p1->print();*/
}