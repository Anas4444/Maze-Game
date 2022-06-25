#include "AI.cpp"
//#include "NodeG.cpp"
//#include "Node.cpp"

std::string path = "Maze/Maze1.txt";
std::vector<std::string> AI::text = AI::fillText(path);
std::vector<AI*> AI::bots;
Coordinate<int> AI::dimensions = AI::fillDimensions();
int** AI::blocks = AI::fillBlocks();

int main() {
    AI* m = new AI(Coordinate<int>(1, 0));
    AI* m1 = new AI(Coordinate<int>(3, 1));
    AI* m2 = new AI(Coordinate<int>(3, 8));
    //AI::multiSearch();
    m->search();
    AI::explore();
    m->clear();

    /*m->shortestPath();
    m->showAll();*/
    //m->alphaShortestPath(4);
    //m->showAll();
    //m->clear();

    /*NodeG* p0 = new NodeG();
    NodeG* p1 = new NodeG(Coordinate<int>(1, 2), p0);
    p1->addPoint(p0);
    p0->print();
    p1->print();*/
}