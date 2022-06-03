#pragma once
#include <fstream>
#include <algorithm>
#include "AStarFrontier.cpp"

class Maze {
    public:
        static std::vector<std::string> text;
        static int** blocks;
        static Pair<int> dimensions;
    private:
        int weight = 0;
        StackFrontier<int>* f;
        Pair<int> destination;
        Pair<int> position;
        std::vector<Node<Pair<int>>*> explored;
        std::vector<std::vector<Node<Pair<int>>*>> allPaths;
        std::vector<Pair<int>> allSearch;
    public:
        Maze();
        Maze(Pair<int> dest, Pair<int> pos);
        virtual ~Maze();
        void clear();
        static std::vector<std::string> fillText(std::string path);
        static Pair<int> fillDimensions();
        static int** fillBlocks();
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
        void eraseFrontier();
        void eraseBlocks();
};