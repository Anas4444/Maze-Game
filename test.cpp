#include "Maze.cpp"

int main() {
    Maze m("Maze/maze1.txt");
    m.print();
    //m.alphaShortestPath();
    //m.shortestPath();
    m.search();
    m.showAll();
}