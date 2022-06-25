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
        AI(Coordinate<int> pos, Coordinate<int> dest);
        virtual ~AI();

        static std::vector<std::string> fillText(std::string path);
        static Coordinate<int> fillDimensions();
        static int** fillBlocks();
        static void explore();
        static void zero();
        static void draw(Node<Coordinate<int>>* node);
        static int roadType(Coordinate<int> road);
        static std::vector<Coordinate<int>> neighbours8(Coordinate<int> location);
        static std::vector<Coordinate<int>> neighbours4(Coordinate<int> location);
        static Coordinate<int> bestPosition8(Coordinate<int> location);
        static Coordinate<int> bestPosition4(Coordinate<int> location);
        static bool allChecked();
        static void multiSearch();

        void setPosition(Coordinate<int> pos);
        void setDestination(Coordinate<int> dest);
        void clearPathFinding();
        void clearSearch();
        void print();
        void showAll(int weight);
        void zeroPath();
        void zero(Node<Coordinate<int>>* node);
        bool isDuplicate(Node<Coordinate<int>>* node);
        bool inExplored(Coordinate<int> Coordinate);
        bool isExplored(Coordinate<int> data, Node<Coordinate<int>>* parent);
        void drawPath(int i);
        void draw();
        

        bool hasPath();
        void shortestPath();
        void alphaShortestPath(int w);
        void search();
        
        void eraseAllPaths();
        void eraseExplored();
        void eraseFrontier();
        void eraseBlocks();
};