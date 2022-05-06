#include "Maze.cpp"

int main() {
    Maze m("Maze/maze1.txt");
    m.print();
    m.alphaShortestPath(0);
    //m.shortestPath();
    m.showAll();
}