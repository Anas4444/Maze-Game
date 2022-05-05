#include "Maze.cpp"

int main() {
    Maze m("Maze/maze1.txt");
    m.print();
    m.alphaShortestPath(10);
    //m.shortestPath();
    m.showAll();
}