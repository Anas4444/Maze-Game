#include <string>
#include <fstream>
#include <algorithm>
#include "AStarFrontier.cpp"

class Maze {
    private:
        int** blocks;
        AStarFrontier<int>* f;
        Pair<int> dimensions;
        Pair<int> destination;
        Node<Pair<int>>* position;
        std::vector<Node<Pair<int>>*> solution;
        std::vector<Node<Pair<int>>*> explored;

    public:
        Maze();
        Maze(std::string path);
        void print();
        bool inExplored(Pair<int> pair);
        std::vector<Node<Pair<int>>*> neighbours(Node<Pair<int>>* location);
        void solve();
};

/*int main() {
    Pair<int> d(4, 7);
    Pair<int> a(0, 0);
    Pair<int> b(2, 1);
    Pair<int> c(4, 4);
    AStarFrontier<int>* sf = new AStarFrontier<int>();
    Node<Pair<int>>* p0 = new Node<Pair<int>>(a);
    Node<Pair<int>>* p1 = new Node<Pair<int>>(b);
    Node<Pair<int>>* p5 = new Node<Pair<int>>(c);
    sf->add(p0);
    sf->add(p1);
    sf->add(p5);
    //sf->print();
    Node<Pair<int>>* p = sf->remove();
    //p->print();
    sf->print();
    /*Node<int>* p = new Node<int>(0);
    Node<int>* p1 = new Node<int>(1, p);
    p1->print();
}*/