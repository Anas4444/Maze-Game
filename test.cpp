#include "AI.cpp"
//#include "NodeG.cpp"
//#include "Node.cpp"

std::string path = "Maze/Maze1.txt";
std::vector<std::string> AI::text = AI::fillText(path);
std::vector<AI*> AI::bots;
Coordinate<int> AI::dimensions = AI::fillDimensions();
int** AI::blocks = AI::fillBlocks();
int AI::frontierType = 3;

int main() {
    AI* m = new AI(Coordinate<int>(1, 0), Coordinate<int>(8, 3));
    AI* m1 = new AI(Coordinate<int>(3, 1));
    AI* m2 = new AI(Coordinate<int>(3, 3));
    //m->print();

    /*AI::multiSearch();
    AI::explore();
    m->clearSearch();*/
    /*m->search();
    AI::explore();
    m->clearSearch();*/

    m->shortestPath();
    m->showAll();
    m->alphaShortestPath(4);
    m->showAll();
    m->clearPathFinding();
    AI::zero();

    /*m->search();
    AI::explore();
    m->clearSearch();*/

    /*NodeG* p0 = new NodeG();
    NodeG* p1 = new NodeG(Coordinate<int>(1, 2), p0);
    p1->addPoint(p0);
    p0->print();
    p1->print();*/
}