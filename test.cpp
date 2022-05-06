#include "Maze.cpp"

int main() {
    Maze m("Maze/maze1.txt");
    m.print();
    m.alphaShortestPath(5);
    //m.shortestPath();
    m.showAll();
}