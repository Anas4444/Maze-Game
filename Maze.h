#pragma once
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
        std::vector<Node<Pair<int>>*> allSearch;
    public:
        Maze();
        Maze(std::string path);
        virtual ~Maze();
        void clear();
        void print();
        void showAll(int weight);
        void explore();
        void zero();
        void zero(Node<Pair<int>>* node);
        bool isDuplicate(Node<Pair<int>>* node);
        bool inExplored(Pair<int> pair);
        bool isExplored(Pair<int> data, Node<Pair<int>>* parent);
        void drawPath(int i);
        void draw();
        void draw(Node<Pair<int>>* node);
        std::vector<Pair<int>> neighbours(Pair<int> location);
        Pair<int> bestPosition(Pair<int> location);
        bool hasPath();
        void shortestPath();
        void alphaShortestPath(int w);
        bool allChecked();
        void search();
        void eraseAllSearch();
        void eraseAllPaths();
        void eraseExplored();
        void erasePosition();
        void eraseFrontier();
        void eraseBlocks();
};