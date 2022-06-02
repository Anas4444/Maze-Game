#include "Maze.cpp"
//#include "NodeG.cpp"
//#include "Node.cpp"

int main() {
    /*Node<Pair<int>>* p0 = new Node<Pair<int>>(Pair<int>(1, 4));
    Node<Pair<int>>* p1 = new Node<Pair<int>>(Pair<int>(1, 2), p0);
    std::cout << p0 << std::endl;
    std::cout << p1 << std::endl;
    Node<Pair<int>>* p;
    p = p1;
    std::cout << *p1 << std::endl;
    delete p1;
    std::cout << *p0 << std::endl;
    //std::cout << p0 << std::endl;
    //std::cout << p;*/

    Maze* m = new Maze("Maze/maze1.txt");
    //m->print();
    m->alphaShortestPath(4);
    //m->shortestPath();
    //m->search();
    m->showAll();
    m->clear();
    /*NodeG* p0 = new NodeG();
    NodeG* p1 = new NodeG(Pair<int>(1, 2), p0);
    p1->addPoint(p0);
    p0->print();
    p1->print();*/

    std::vector<int*> a;
    int* f0 = new int[2] {1, 2};
    int* f1 = new int[3] {5, 6, 7};
    int* f2 = new int[5] {85, 55, 12, 45, 89};
    a.push_back(f0);
    a.push_back(f1);
    a.push_back(f2);
    std::cout << "\nf";
    delete[] a[0];
    delete[] a[1];
    delete[] a[2];
    a.clear();
    std::cout << "f";
    std::cout << "blabla";
}