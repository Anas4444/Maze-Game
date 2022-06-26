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
        static int frontierType;

    private:
        int weight = 0;
        int neighbourType = 0;
        
        StackFrontier<int>* frontier;
        Coordinate<int> destination;        
        Coordinate<int> position;
        std::vector<Node<Coordinate<int>>*> explored;
        std::vector<std::vector<Node<Coordinate<int>>*>> allPaths;
        std::vector<Coordinate<int>> allSearch;
        
    public:
    //Constructors & Destructors
        AI();
        AI(const Coordinate<int>& pos);
        AI(const Coordinate<int>& pos, const Coordinate<int>& dest);
        AI(const Coordinate<int>& pos, const Coordinate<int>& dest, int neighbourType);
        AI(const Coordinate<int>& pos, const Coordinate<int>& dest, int neighbourType, int weight);
        virtual ~AI();

    //Static functions
        static std::vector<std::string> fillText(const std::string& path);
        static Coordinate<int> fillDimensions();
        static int** fillBlocks();

        static void explore();
        static void draw(Node<Coordinate<int>>* node);
        static void zero();

        static int roadType(const Coordinate<int>& road);

        static std::vector<Coordinate<int>> neighbours4(const Coordinate<int>& location);
        static Coordinate<int> bestPosition4(const Coordinate<int>& location);

        static std::vector<Coordinate<int>> neighbours8(const Coordinate<int>& location);
        static Coordinate<int> bestPosition8(const Coordinate<int>& location);

        static void multiSearch();

    //Methods
        void initFrontier();

        std::vector<Coordinate<int>> getNeighbours(const Coordinate<int>& location);
        Coordinate<int> getBestPosition(const Coordinate<int>& location);

        void setNeighbourType(int nType);
        void setPosition(const Coordinate<int>& pos);
        void setDestination(const Coordinate<int>& dest);
        void setWeight(int weight);

        void showAll(int weight);
        void print();
        void draw();
        void drawPath(const int& i);

        void zeroPath();
        void zero(Node<Coordinate<int>>* node);

        bool isDuplicate(Node<Coordinate<int>>* node);
        bool inExplored(const Coordinate<int>& Coordinate);
        bool isExplored(const Coordinate<int>& data, Node<Coordinate<int>>* parent);
        bool allChecked();
        bool hasPath();

        void shortestPath();
        void alphaShortestPath(int w);
        void search();
        
        void clearPathFinding();
        void clearSearch();

        void eraseAllPaths();
        void eraseExplored();
        void eraseFrontier();
        void eraseBlocks();
};