#include "Maze.cpp"
//#include "NodeG.cpp"
//#include "Node.cpp"

int main() {
    Maze* m = new Maze("Maze/maze1.txt");
    //m->print();
    m->alphaShortestPath(4);
    //m->shortestPath();
    //m->search();

    /*NodeG* p0 = new NodeG();
    NodeG* p1 = new NodeG(Pair<int>(1, 2), p0);
    p1->addPoint(p0);
    p0->print();
    p1->print();*/
}