#include "Maze.h"

Maze::Maze() {}

Maze::Maze(std::string path) {
    std::string text;
    std::ifstream file(path);
    std::vector<std::string> allText;
    while(std::getline(file, text)) {
        allText.push_back(text);
    }
    file.close();
    this->dimensions.set(allText.size(), allText[0].length());
    this->blocks = new int*[dimensions.x];
    for (int i=0; i<dimensions.x; i++) this->blocks[i] = new int[dimensions.y];
    for (int i=0; i<dimensions.x; i++) {
        for (int j=0; j<dimensions.y; j++) {
            if (allText[i][j]=='P') {
                this->position = new Node(Pair<int>(i, j));
                this->blocks[i][j] = 1;
            }
            else if (allText[i][j]=='L') {
                this->destination.set(i, j);
                this->blocks[i][j] = 0;
            }
            else if (allText[i][j]==' ') this->blocks[i][j] = 0;
            else this->blocks[i][j] = -1;
        }
    }
}

void Maze::print() {
    for (int i=0; i<this->dimensions.x; i++) {
        for (int j=0; j<this->dimensions.y; j++) {
            if (this->blocks[i][j]==-1) std::cout << '&';
            else if (this->position->getData()==Pair(i, j)) std::cout << 'P'; 
            else if (this->destination==Pair(i, j)) std::cout << 'L';
            else if (this->blocks[i][j]>=0) std::cout << ' ';
            else if (this->blocks[i][j]==-2) std::cout << '*';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<Node<Pair<int>>*> Maze::neighbours(Node<Pair<int>>* location) {
    Pair<int> loc = location->getData();
    Pair<int> nghb[8] {Pair<int>(loc.x+1, loc.y), Pair<int>(loc.x-1, loc.y),
                       Pair<int>(loc.x, loc.y+1), Pair<int>(loc.x, loc.y-1),
                       Pair<int>(loc.x+1, loc.y+1), Pair<int>(loc.x+1, loc.y-1),
                       Pair<int>(loc.x-1, loc.y+1), Pair<int>(loc.x-1, loc.y-1)}; 
    std::vector<Node<Pair<int>>*> result;
    for (int i=0; i<8; i++) {
        if (nghb[i].x < this->dimensions.x && nghb[i].y < this->dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && this->blocks[nghb[i].x][nghb[i].y]!=-1)
            result.push_back(new Node(nghb[i], location));
    }
    return result;
}

bool Maze::inExplored(Pair<int> pair) {
    return this->blocks[pair.x][pair.y]>0;
    /*for (int i=0; i<this->explored.size(); i++) {
        if (pair==this->explored[i]->getData()) return true;
    }
    return false;*/
}

void Maze::shortestPath() {
    f = new AStarFrontier<int>(&this->destination, this->dimensions.x, this->dimensions.y);
    //f->printHBoard();
    //f = new QueueFrontier<int>();
    Node<Pair<int>>* node = new Node<Pair<int>>(*(this->position));
    f->add(new Node<Pair<int>>(*node));
    while(node->getData()!=destination && !f->empty()) {
        //f->printOne();
        node = f->remove();
        //std::cout << "Best One : ";
        //node->printOne();
        //std::cout << " | distance : " << f->distance(node->getData()) << "\n\n";
        Pair<int> pos = node->getData();
        this->blocks[pos.x][pos.y]++;
        //this->explored.push_back(new Node<Pair<int>>(*node));
        std::vector<Node<Pair<int>>*> neighb = neighbours(node);
        for (int i=0; i<neighb.size(); i++) {
            if (!inExplored(neighb[i]->getData()) && !f->inFrontier(neighb[i])) 
                f->add(new Node<Pair<int>>(*neighb[i]));
        }
    }
    Node<Pair<int>>* p = node;
    while (p != nullptr) {
        Pair<int> pos = p->getData();
        this->blocks[pos.x][pos.y]=-2;
        this->solution.push_back(new Node<Pair<int>>(*p));
        p = p->parent;
    }
    std::reverse(this->solution.begin(), this->solution.end());
    for (int i=0; i<this->solution.size(); i++) {
        Pair<int> p = this->solution[i]->getData();
        //this->solution[i]->printOne();
        //std::cout << "distance : " << f->distance(p) << std::endl;
    }
}

void Maze::solveAll(int w) {
    std::vector<Node<Pair<int>>*> allNodes;
    f = new AStarFrontier<int>(&this->destination, this->dimensions.x, this->dimensions.y);
    Node<Pair<int>>* node = new Node<Pair<int>>(*(this->position));
    f->add(new Node<Pair<int>>(*node));
    int k=0;
    while(!f->empty() && k<w) {
        f->printOne();
        node = f->remove();
        std::cout << "Best One : ";
        node->printOne();
        std::cout << " | distance : " << f->distance(node->getData()) << "\n\n";
        if (node->getData()==destination) {
            k++;
            allNodes.push_back(new Node<Pair<int>>(*node));
            std::cout << k <<" Explored\n";
        }
        else {
            Pair<int> pos = node->getData();
            this->blocks[pos.x][pos.y]++;
        }
        std::vector<Node<Pair<int>>*> neighb = neighbours(node);
        for (int i=0; i<neighb.size(); i++) {
            if (!inExplored(neighb[i]->getData()) && !f->inFrontier(neighb[i]))
                f->add(new Node<Pair<int>>(*neighb[i]));
        }
    }

    std::cout << allNodes.size() << std::endl;
    for (int i=0; i<allNodes.size(); i++) {
        std::vector<Node<Pair<int>>*> path;
        Node<Pair<int>>* p = allNodes[i];
        while (p != nullptr) {
            Pair<int> pos = p->getData();
            path.push_back(p);
            this->blocks[pos.x][pos.y]=-2;
            p = p->parent;
        }
        std::reverse(path.begin(), path.end());
        this->allPaths.push_back(path);
    }

    /*for (int i=0; i<this->allPaths.size(); i++) {
        for (int j=0; j<this->allPaths[i].size(); j++) {
            this->allPaths[i][j]->printOne();
            std::cout << "\n";
        }
        std::cout << "\n";
    }*/
}