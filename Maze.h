#include <string>
#include <fstream>
#include <algorithm>
#include "AStarFrontier.cpp"

class Maze {
    private:
        int weight = 0;
        int** blocks;
        StackFrontier<int>* f;
        Pair<int> dimensions;
        Pair<int> destination;
        Node<Pair<int>>* position;
        std::vector<Node<Pair<int>>*> explored;
        std::vector<std::vector<Node<Pair<int>>*>> allPaths;
    public:
        Maze();
        Maze(std::string path);
        void print();
        void showAll(int weight);
        void explore();
        void zero();
        void zero(Node<Pair<int>>* node);
        bool isDuplicate(Node<Pair<int>>* node);
        bool inExplored(Pair<int> pair);
        bool isExplored(Node<Pair<int>>* node);
        void drawPath(int i);
        void draw();
        void draw(Node<Pair<int>>* node);
        std::vector<Node<Pair<int>>*> neighbours(Node<Pair<int>>* location);
        void shortestPath();
        void alphaShortestPath(int w);
};