#include "Maze.cpp"

int main() {
    Maze m("Maze/maze1.txt");
    m.print();
    m.solveAll(5);
    //m.shortestPath();
    m.print();
}