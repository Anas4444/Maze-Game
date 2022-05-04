#include "Maze.cpp"

int main() {
    Maze m("Maze/maze1.txt");
    m.print();
    m.solveAll(7);
    m.drawAlphaPath(7);
    //m.shortestPath();
    m.print();
}