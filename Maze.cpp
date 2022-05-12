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
                this->blocks[i][j] = 0;
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

void Maze::showAll(int w=0) {
    if (w==0) w = this->weight;
    this->explore();
    for (int i=0; i<w; i++) {
        this->drawPath(i+1);
        this->print();
        this->zero();
    }
}

void Maze::explore() {
    for (int i=0; i<this->dimensions.x; i++) {
        for (int j=0; j<this->dimensions.y; j++) {
            if (this->blocks[i][j]==-1) std::cout << '&';
            else std::cout << this->blocks[i][j];
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
}

bool Maze::isExplored(Node<Pair<int>>* node) {
    for (int i=0; i<this->explored.size(); i++) {
        if (this->explored[i]->parent && node->parent) 
            if (this->explored[i]->parent->getData()==node->getData() && this->explored[i]->equals(node->parent)) return true;
    }
    return false;
}

bool Maze::isDuplicate(Node<Pair<int>>* node) {
    Node<Pair<int>>* p = node;
    std::vector<Node<Pair<int>>*> path;
    while (p != nullptr) {
        Pair<int> pos = p->getData();
        path.push_back(new Node<Pair<int>>(*p));
        p = p->parent;
    }
    int n = path.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (path[i]->getData()==path[j]->getData() && i!=j) return true;
        }
    }
    return false;
}

void Maze::zero() {
    for (int i=0; i<this->dimensions.x; i++) {
        for (int j=0; j<this->dimensions.y; j++) {
            if (this->blocks[i][j]==-2) this->blocks[i][j]=0;
        }
    }
}

void Maze::zero(Node<Pair<int>>* node) {
    Node<Pair<int>>* p = node;
    while (p != nullptr) {
        Pair<int> pos = p->getData();
        this->blocks[pos.x][pos.y] = 0;
        p = p->parent;
    }
}

void Maze::drawPath(int alpha=1) {
    if (this->allPaths.size()>alpha-1) {
        for (int i=0; i<this->allPaths[alpha-1].size(); i++) {
            Pair<int> pos = this->allPaths[alpha-1][i]->getData();
            this->blocks[pos.x][pos.y]=-2;
        }
    }
}

void Maze::draw() {
    for (int i=0; i<this->allPaths.size(); i++) {
        for (int j=0; j<this->allPaths[i].size(); j++) {
            Pair<int> pos = this->allPaths[i][j]->getData();
            this->blocks[pos.x][pos.y]=-2;
        }
    }
}

void Maze::draw(Node<Pair<int>>* node) {
    Node<Pair<int>>* p = node;
    while (p != nullptr) {
        Pair<int> pos = p->getData();
        this->blocks[pos.x][pos.y] = -2;
        p = p->parent;
    }
} 

bool Maze::allChecked() {
    for (int i=0; i<this->dimensions.x; i++) {
        for (int j=0; j<this->dimensions.y; j++) {
            if (this->blocks[i][j]>0) {
                std::vector<Node<Pair<int>>*> neighbors = this->neighbours(new Node<Pair<int>>(Pair<int>(i, j)));
                for (int k=0; k<neighbors.size(); k++) {
                    Pair<int> pos = neighbors[k]->getData();
                    if (this->blocks[pos.x][pos.y]==0) return false;
                }
            }
        }
    }
    return true;
}

Node<Pair<int>>* Maze::bestPosition(Node<Pair<int>>* location) {
    Pair<int> loc = location->getData();
    Pair<int> nghb[8] {Pair<int>(loc.x+1, loc.y), Pair<int>(loc.x-1, loc.y),
                       Pair<int>(loc.x, loc.y+1), Pair<int>(loc.x, loc.y-1),
                       Pair<int>(loc.x+1, loc.y+1), Pair<int>(loc.x+1, loc.y-1),
                       Pair<int>(loc.x-1, loc.y+1), Pair<int>(loc.x-1, loc.y-1)};
    Node<Pair<int>>* node;
    int i=0;
    for (; i<8; i++) {
        if (nghb[i].x < this->dimensions.x && nghb[i].y < this->dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && this->blocks[nghb[i].x][nghb[i].y]!=-1) {
            node = new Node(nghb[i], location);
            break;
        }
    }
    for (; i<8; i++) {
        bool notBlockandInBoard = nghb[i].x < this->dimensions.x && nghb[i].y < this->dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && this->blocks[nghb[i].x][nghb[i].y]!=-1;
        if (!notBlockandInBoard) continue;
        Pair<int> pos = node->getData();
        if (this->blocks[pos.x][pos.y]>this->blocks[nghb[i].x][nghb[i].y]) node = new Node(nghb[i], location);
    }
    return node;
}

void Maze::shortestPath() {
    f = new AStarFrontier<int>(&this->destination, this->dimensions.x, this->dimensions.y);
    std::vector<Node<Pair<int>>*> path;
    f->printHBoard();
    Node<Pair<int>>* node = new Node<Pair<int>>(*(this->position));
    f->add(new Node<Pair<int>>(*node));
    while(node->getData()!=destination && !f->empty()) {
        f->printOne();
        node = f->remove();
        std::cout << "Best One : ";
        node->printOne();
        std::cout << " | distance : " << f->distance(node->getData()) << "\n\n";
        Pair<int> pos = node->getData();
        this->blocks[pos.x][pos.y]++;
        this->explore();
        std::vector<Node<Pair<int>>*> neighb = neighbours(node);
        for (int i=0; i<neighb.size(); i++) {
            if (!inExplored(neighb[i]->getData()) && !f->inFrontier(neighb[i])) 
                f->add(new Node<Pair<int>>(*neighb[i]));
        }
    }
    Node<Pair<int>>* p = node;
    while (p != nullptr) {
        Pair<int> pos = p->getData();
        path.push_back(new Node<Pair<int>>(*p));
        p = p->parent;
    }
    std::reverse(path.begin(), path.end());
    this->allPaths.push_back(path);
}

void Maze::alphaShortestPath(int w = 0) {
    this->weight = w;
    std::vector<Node<Pair<int>>*> allNodes;
    f = new AStarFrontier<int>(&this->destination, this->dimensions.x, this->dimensions.y);
    f->printHBoard();
    Node<Pair<int>>* node = new Node<Pair<int>>(*(this->position));
    f->add(new Node<Pair<int>>(*node));
    int k=0;
    int d=0;
    while(!f->empty() && (k<w || w<=0) && d<10) {
        //f->printOne();
        node = f->remove();
        //std::cout << "Best One : ";
        //node->printOne();
        //std::cout << " | distance : " << f->distance(node->getData()) << "\n\n";
        while (node->getData()==destination && (k<w || w<=0)) {
            if (!isDuplicate(node)) {
                node->print();
                std::vector<Node<Pair<int>>*> path;
                Node<Pair<int>>* p = node;
                while (p != nullptr) {
                    path.push_back(p);
                    p = p->parent;
                }
                
                std::reverse(path.begin(), path.end());
                this->allPaths.push_back(path);
                d = 0;
                k++;

                Pair<int> pos = node->getData();
                this->blocks[pos.x][pos.y]++;
                this->explored.push_back(new Node<Pair<int>>(*node));
            }
            d++;
            std::cout << k <<" Explored\n\n";
            //f->printOne();
            node = f->remove();
            //std::cout << "Best One : ";
            //node->printOne();
            //std::cout << " | distance : " << f->distance(node->getData()) << "\n\n";
        }
        Pair<int> pos = node->getData();
        this->blocks[pos.x][pos.y]++;
        this->explored.push_back(new Node<Pair<int>>(*node));
        this->explore();
        std::vector<Node<Pair<int>>*> neighb = neighbours(node);
        for (int i=0; i<neighb.size(); i++) {
            if (!isExplored(neighb[i]))
                f->add(new Node<Pair<int>>(*neighb[i]));
        }
    }
    if (this->weight>this->allPaths.size() || this->weight<=0)
        this->weight = this->allPaths.size();
}

void Maze::search() {
    this->allSearch.push_back(new Node<Pair<int>>(*position));
    Pair<int> pos = position->getData();
    this->blocks[pos.x][pos.y]++;
    //this->explore();
    while (true) {
        Node<Pair<int>>* newNode = this->bestPosition(position);
        Pair<int> pos = position->getData();
        Pair<int> newPos = newNode->getData();
        if (this->blocks[newPos.x][newPos.y]>0 && this->blocks[pos.x][pos.y]==1) {
            if (this->allChecked()) break;
        }
        this->blocks[newPos.x][newPos.y]++;
        //this->explore();
        position = newNode;
        allSearch.push_back(new Node<Pair<int>>(*position));
    }
}