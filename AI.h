#pragma once
#include <fstream>
#include <algorithm>
#include "AStarFrontier.cpp"

class AI {
    public:
        static std::vector<AI*> bots;
        static std::vector<std::string> text;
        static int** blocks;
        static Coordinate<int> dimensions;
    private:
        int weight = 0;
        StackFrontier<int>* frontier;
        Coordinate<int> destination;
        Coordinate<int> position;
        std::vector<Node<Coordinate<int>>*> explored;
        std::vector<std::vector<Node<Coordinate<int>>*>> allPaths;
        std::vector<Coordinate<int>> allSearch;
    public:
        AI();
        AI(Coordinate<int> pos);
        AI(Coordinate<int> dest, Coordinate<int> pos);
        virtual ~AI();
        void setPosition(Coordinate<int> pos);
        void setDestination(Coordinate<int> dest);
        void clear();
        static std::vector<std::string> fillText(std::string path);
        static Coordinate<int> fillDimensions();
        static int** fillBlocks();
        void print();
        void showAll(int weight);
        static void explore();
        static void zero();
        void zeroPath();
        void zero(Node<Coordinate<int>>* node);
        bool isDuplicate(Node<Coordinate<int>>* node);
        bool inExplored(Coordinate<int> Coordinate);
        bool isExplored(Coordinate<int> data, Node<Coordinate<int>>* parent);
        void drawPath(int i);
        void draw();
        void draw(Node<Coordinate<int>>* node);
        std::vector<Coordinate<int>> neighbours(Coordinate<int> location);
        Coordinate<int> bestPosition(Coordinate<int> location);
        bool hasPath();
        void shortestPath();
        void alphaShortestPath(int w);
        bool allChecked();
        void search();
        static void multiSearch();
        void eraseAllSearch();
        void eraseAllPaths();
        void eraseExplored();
        void eraseFrontier();
        void eraseBlocks();
};