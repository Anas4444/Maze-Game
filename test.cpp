#include "Maze.cpp"
//#include "NodeG.cpp"
//#include "Node.cpp"

std::string path = "Maze/maze1.txt";
std::vector<std::string> Maze::text = Maze::fillText(path);
Pair<int> Maze::dimensions = Maze::fillDimensions();
int** Maze::blocks = Maze::fillBlocks();

int main() {
    Maze* m = new Maze();
    //m->print();
    //m->alphaShortestPath(4);
    m->search();
    m->showAll();
    m->clear();
    m->shortestPath();
    m->showAll();
    m->clear();
    //m->search();

    /*NodeG* p0 = new NodeG();
    NodeG* p1 = new NodeG(Pair<int>(1, 2), p0);
    p1->addPoint(p0);
    p0->print();
    p1->print();*/
}