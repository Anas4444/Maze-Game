#include "AI.h"

AI::AI() {
    AI::bots.push_back(this);
    for (int i=0; i<AI::dimensions.y; i++) {
        for (int j=0; j<AI::dimensions.x; j++) {
            if (AI::blocks[i][j]==-3) {
                this->position = Coordinate<int>(j, i);
                AI::blocks[i][j] = 0;
            }
            else if (AI::blocks[i][j]==-4) {
                this->destination = Coordinate<int>(j, i);
                AI::blocks[i][j] = 0;
            }
        }
    }
}

AI::AI(Coordinate<int> pos) {
    AI::bots.push_back(this);
    this->position = pos;
    this->destination = Coordinate<int>(8, 3);
}

AI::AI(Coordinate<int> pos, Coordinate<int> dest) {
    AI::bots.push_back(this);
    this->destination = dest;
    this->position = pos;
}

AI::~AI() {
    int n = AI::bots.size();
    for (int i=0; i<n-1; i++) {
        std::cout << AI::bots[i] << " | ";
    }
    std::cout << AI::bots[n-1] << "\n";
    for (int i=0; i<n; i++) {
        if (AI::bots[i]==this) {
            AI::bots.erase(AI::bots.begin()+i);
            break;
        }
    }
    this->clearPathFinding();
    this->clearSearch();

}

void AI::setPosition(Coordinate<int> pos)
{
    this->position = pos;
}

void AI::setDestination(Coordinate<int> dest)
{
    this->destination = dest;
}

void AI::clearSearch() {
    int n = this->allSearch.size();
    if (n==0) return;
    this->allSearch.clear();
    this->allSearch.shrink_to_fit();
}

void AI::clearPathFinding() {
    this->eraseExplored();
    this->eraseFrontier();
    this->eraseAllPaths();
    this->weight = 0;
}

void AI::eraseExplored() {
    //for (int i=0; i<this->explored.size(); i++) delete this->explored[i];
    this->explored.clear();
    this->explored.shrink_to_fit();
}

void AI::eraseBlocks() {
    for (int i=0; i<AI::dimensions.y; i++) delete[] AI::blocks[i];
    delete[] AI::blocks;
}

void AI::eraseFrontier() {
    delete this->frontier;
}

void AI::eraseAllPaths() {
    int n = this->allPaths.size();
    if (n==0) return;
    for (int i=0; i<n; i++) {
        int m = this->allPaths[i].size();
        if (m==0) continue;
        //delete this->allPaths[i][m-1];
        this->allPaths[i].clear();
        this->allPaths[i].shrink_to_fit();
    }
    this->allPaths.clear();
    this->allPaths.shrink_to_fit();
}

std::vector<std::string> AI::fillText(std::string path) {
    std::string text;
    std::ifstream file(path);
    std::vector<std::string> allText;
    while(std::getline(file, text)) {
        allText.push_back(text);
    }
    file.close();
    return allText;
}

Coordinate<int> AI::fillDimensions() {
    return Coordinate<int>(AI::text[0].length(), AI::text.size());
}

int** AI::fillBlocks() {
    int** block = new int*[dimensions.y];
    for (int i=0; i<AI::dimensions.y; i++) block[i] = new int[AI::dimensions.x];
    for (int i=0; i<AI::dimensions.y; i++) {
        for (int j=0; j<AI::dimensions.x; j++) {
            if (AI::text[i][j]!='&') block[i][j] = 0;
            else block[i][j] = -1;
        }
    }
    return block;
}

void AI::print() {
    for (int i=0; i<AI::dimensions.y; i++) {
        for (int j=0; j<AI::dimensions.x; j++) {
            if (AI::blocks[i][j]==-1) std::cout << '&';
            else if (this->position==Coordinate(j, i)) std::cout << 'P'; 
            else if (this->destination==Coordinate(j, i)) std::cout << 'L';
            else if (AI::blocks[i][j]>=0) std::cout << ' ';
            else if (AI::blocks[i][j]==-2) std::cout << '*';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void AI::showAll(int w=0) {
    if (w==0) w = this->weight;
    for (int i=0; i<w; i++) {
        this->drawPath(i+1);
        this->print();
        this->zeroPath();
    }
}

void AI::explore() {
    for (int i=0; i<AI::dimensions.y; i++) {
        for (int j=0; j<AI::dimensions.x; j++) {
            if (AI::blocks[i][j]==-1) std::cout << '&';
            else std::cout << AI::blocks[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void AI::zeroPath() {
    for (int i=0; i<AI::dimensions.y; i++) {
        for (int j=0; j<AI::dimensions.x; j++) {
            if (AI::blocks[i][j]==-2) AI::blocks[i][j]=0;
        }
    }
}

void AI::zero() {
    for (int i=0; i<AI::dimensions.y; i++) {
        for (int j=0; j<AI::dimensions.x; j++) {
            if (AI::blocks[i][j]>0 || AI::blocks[i][j]==-2) AI::blocks[i][j]=0;
        }
    }
}

void AI::zero(Node<Coordinate<int>>* node) {
    Node<Coordinate<int>>* p = node;
    while (p != nullptr) {
        Coordinate<int> pos = p->getData();
        AI::blocks[pos.y][pos.x] = 0;
        p = p->parent;
    }
}

int AI::roadType(Coordinate<int> road)
{
    if (AI::blocks[road.y][road.x]==-1) return -1;
    std::vector<Coordinate<int>> neigh = AI::neighbours4(road);  
    int n = neigh.size();
    if (n==4) return 11;
    if (n==0) return 0;
    if (n==3) {
        if (road.x==neigh[0].x && road.x==neigh[1].x || road.x!=neigh[0].x && road.x!=neigh[1].x) {
            if (road.x==neigh[2].x) {
                if (road.y<neigh[2].y) return 7;
                else return 9;
            }
            else {
                if (road.x<neigh[2].x) return 8;
                else return 10;
            }
        }
        else if (road.x==neigh[0].x && road.x!=neigh[1].x && road.x!=neigh[2].x || road.x!=neigh[0].x && road.x==neigh[1].x && road.x==neigh[2].x) {
            if (road.x==neigh[0].x) {
                if (road.y<neigh[0].y) return 7;
                else return 9;
            }
            else {
                if (road.x<neigh[0].x) return 8;
                else return 10;
            }
        }
        else {
            if (road.x==neigh[1].x) {
                if (road.y<neigh[1].y) return 7;
                else return 9;
            }
            else {
                if (road.x<neigh[1].x) return 8;
                else return 10;
            }
        }
    }
    if (road.x==neigh[1].x && road.y==neigh[0].y) {
        if (road.x<neigh[0].x && road.y<neigh[1].y) return 3;
        if (road.x<neigh[0].x && road.y>neigh[1].y) return 4;
        if (road.x>neigh[0].x && road.y>neigh[1].y) return 5;
        if (road.x>neigh[0].x && road.y<neigh[1].y) return 6;
    }
    if (road.x==neigh[0].x && road.y==neigh[1].y) {
        if (road.x<neigh[1].x && road.y<neigh[0].y) return 3;
        if (road.x<neigh[1].x && road.y>neigh[0].y) return 4;
        if (road.x>neigh[1].x && road.y>neigh[0].y) return 5;
        if (road.x>neigh[1].x && road.y<neigh[0].y) return 6;
    }
    if (road.x==neigh[0].x) return 1;
    else return 2;
}

void AI::drawPath(int alpha=1) {
    if (this->allPaths.size()>alpha-1) {
        for (int i=0; i<this->allPaths[alpha-1].size(); i++) {
            Coordinate<int> pos = this->allPaths[alpha-1][i]->getData();
            AI::blocks[pos.y][pos.x]=-2;
        }
    }
}

void AI::draw() {
    for (int i=0; i<this->allPaths.size(); i++) {
        for (int j=0; j<this->allPaths[i].size(); j++) {
            Coordinate<int> pos = this->allPaths[i][j]->getData();
            AI::blocks[pos.y][pos.x]=-2;
        }
    }
}

void AI::draw(Node<Coordinate<int>>* node) {
    Node<Coordinate<int>>* p = node;
    while (p != nullptr) {
        Coordinate<int> pos = p->getData();
        AI::blocks[pos.y][pos.x] = -2;
        p = p->parent;
    }
} 

bool AI::inExplored(Coordinate<int> pair) {
    for (int i=0; i<this->explored.size(); i++) {
        Coordinate<int> pos = this->explored[i]->getData();
        if (pos==pair) return true;
    }
    return false;
    //return AI::blocks[pair.x][pair.y]>0;
}

bool AI::isExplored(Coordinate<int> data, Node<Coordinate<int>>* parent) {
    for (int i=0; i<this->explored.size(); i++) {
        if (this->explored[i]->parent && parent) 
            if (this->explored[i]->parent->getData()==data && this->explored[i]->equals(parent)) return true;
    }
    return false;
}

bool AI::isDuplicate(Node<Coordinate<int>>* node) {
    Node<Coordinate<int>>* p = node;
    std::vector<Node<Coordinate<int>>*> path;
    while (p != nullptr) {
        Coordinate<int> pos = p->getData();
        path.push_back(p);
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

bool AI::allChecked() {
    for (int i=0; i<AI::dimensions.y; i++) {
        for (int j=0; j<AI::dimensions.x; j++) {
            if (AI::blocks[i][j]>0) {
                std::vector<Coordinate<int>> neighbors = AI::neighbours4(Coordinate<int>(j, i));
                for (int k=0; k<neighbors.size(); k++) {
                    Coordinate<int> pos = neighbors[k];
                    if (AI::blocks[pos.y][pos.x]==0) return false;
                }
            }
        }
    }
    return true;
}

Coordinate<int> AI::bestPosition8(Coordinate<int> loc) {
    Coordinate<int> nghb[8] {Coordinate<int>(loc.x+1, loc.y), Coordinate<int>(loc.x-1, loc.y),
                             Coordinate<int>(loc.x, loc.y+1), Coordinate<int>(loc.x, loc.y-1),
                             Coordinate<int>(loc.x+1, loc.y+1), Coordinate<int>(loc.x+1, loc.y-1),
                             Coordinate<int>(loc.x-1, loc.y+1), Coordinate<int>(loc.x-1, loc.y-1)};
    Coordinate<int> pos;
    int i=0;
    for (; i<8; i++) {
        if (nghb[i].x < AI::dimensions.x && nghb[i].y < AI::dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && AI::blocks[nghb[i].y][nghb[i].x]!=-1) {
            pos = nghb[i];
            break;
        }
    }
    for (; i<8; i++) {
        bool notBlockandInBoard = nghb[i].x < AI::dimensions.x && nghb[i].y < AI::dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && AI::blocks[nghb[i].y][nghb[i].x]!=-1;
        if (!notBlockandInBoard) continue;
        if (AI::blocks[pos.y][pos.x] > AI::blocks[nghb[i].y][nghb[i].x]) pos = nghb[i];
    }
    return pos;
}

Coordinate<int> AI::bestPosition4(Coordinate<int> loc) {
    Coordinate<int> nghb[4] {Coordinate<int>(loc.x+1, loc.y), Coordinate<int>(loc.x-1, loc.y),
                             Coordinate<int>(loc.x, loc.y+1), Coordinate<int>(loc.x, loc.y-1)};
    Coordinate<int> pos;
    int i=0;
    for (; i<4; i++) {
        if (nghb[i].x < AI::dimensions.x && nghb[i].y < AI::dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && AI::blocks[nghb[i].y][nghb[i].x]!=-1) {
            pos = nghb[i];
            break;
        }
    }
    for (; i<4; i++) {
        bool notBlockandInBoard = nghb[i].x < AI::dimensions.x && nghb[i].y < AI::dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && AI::blocks[nghb[i].y][nghb[i].x]!=-1;
        if (!notBlockandInBoard) continue;
        if (AI::blocks[pos.y][pos.x] > AI::blocks[nghb[i].y][nghb[i].x]) pos = nghb[i];
    }
    return pos;
}

std::vector<Coordinate<int>> AI::neighbours8(Coordinate<int> loc) {
    Coordinate<int> nghb[8] {Coordinate<int>(loc.x+1, loc.y), Coordinate<int>(loc.x-1, loc.y),
                             Coordinate<int>(loc.x, loc.y+1), Coordinate<int>(loc.x, loc.y-1),
                             Coordinate<int>(loc.x+1, loc.y+1), Coordinate<int>(loc.x+1, loc.y-1),
                             Coordinate<int>(loc.x-1, loc.y+1), Coordinate<int>(loc.x-1, loc.y-1)}; 
    std::vector<Coordinate<int>> result;
    for (int i=0; i<8; i++) {
        if (nghb[i].x < AI::dimensions.x && nghb[i].y < AI::dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && AI::blocks[nghb[i].y][nghb[i].x]!=-1)
            result.push_back(nghb[i]);
    }
    return result;
}

std::vector<Coordinate<int>> AI::neighbours4(Coordinate<int> loc) {
    Coordinate<int> nghb[4] {Coordinate<int>(loc.x+1, loc.y), Coordinate<int>(loc.x-1, loc.y),
                             Coordinate<int>(loc.x, loc.y+1), Coordinate<int>(loc.x, loc.y-1)}; 
    std::vector<Coordinate<int>> result;
    for (int i=0; i<4; i++) {
        if (nghb[i].x < AI::dimensions.x && nghb[i].y < AI::dimensions.y && nghb[i].x >= 0 && nghb[i].y >= 0 && AI::blocks[nghb[i].y][nghb[i].x]!=-1)
            result.push_back(nghb[i]);
    }
    return result;
}

bool AI::hasPath() {
    this->clearPathFinding();
    this->initFrontier();
    std::vector<Node<Coordinate<int>>*> path;
    //this->frontier->printHBoard();
    Node<Coordinate<int>>* node = new Node<Coordinate<int>>(this->position);
    this->frontier->add(node);
    while(node->getData()!=destination && !this->frontier->empty()) {
        //this->frontier->printOne();
        node = this->frontier->remove();
        this->explored.push_back(node);
        //std::cout << "Best One : ";
        //node->printOne();
        //std::cout << " | distance : " << this->frontier->distance(node->getData()) << "\n\n";
        Coordinate<int> pos = node->getData();
        AI::blocks[pos.y][pos.x]++;
        //this->explore();
        std::vector<Coordinate<int>> neighb = AI::neighbours4(node->getData());
        for (int i=0; i<neighb.size(); i++) {
            if (!inExplored(neighb[i]) && !this->frontier->inFrontier(neighb[i])) {
                Node<Coordinate<int>>* newNode = new Node(neighb[i], node);
                this->frontier->add(newNode);
            } 
        }
    }
    if (node->getData()!=destination) {
        return false;
    }
    return true;
}

void AI::shortestPath() {
    this->clearPathFinding();
    this->weight = 1;
    this->initFrontier();
    std::vector<Node<Coordinate<int>>*> path;
    this->frontier->printHBoard();
    Node<Coordinate<int>>* node = new Node<Coordinate<int>>(this->position);
    this->frontier->add(node);
    while(node->getData()!=destination && !this->frontier->empty()) {
        //this->frontier->printOne();
        node = this->frontier->remove();
        //std::cout << "Best One : ";
        //node->printOne();
        //std::cout << " | distance : " << frontier->distance(node->getData()) << "\n\n";
        Coordinate<int> pos = node->getData();
        AI::blocks[pos.y][pos.x]++;
        //this->explore();
        std::vector<Coordinate<int>> neighb = AI::neighbours4(node->getData());
        for (int i=0; i<neighb.size(); i++) {
            if (!inExplored(neighb[i]) && !this->frontier->inFrontier(neighb[i])) {
                Node<Coordinate<int>>* newNode = new Node(neighb[i], node);
                this->frontier->add(newNode);
            }

        }
    }
    Node<Coordinate<int>>* p = node;
    while (p != nullptr) {
        path.push_back(p);
        p = p->parent;
    }
    std::reverse(path.begin(), path.end());
    this->allPaths.push_back(path);
}

void AI::alphaShortestPath(int w = 0) {
    if (!hasPath()) {
        this->weight = 0;
        return;
    }
    this->clearPathFinding();
    this->weight = w;
    std::vector<Node<Coordinate<int>>*> allNodes;
    this->initFrontier();
    this->frontier->printHBoard();
    Node<Coordinate<int>>* node = new Node<Coordinate<int>>(this->position);
    this->frontier->add(node);
    int k=0;
    int d=0;
    while(!this->frontier->empty() && (k<w || w<=0) && d<10) {
        //frontier->printOne();
        node = this->frontier->remove();
        //std::cout << "Best One : ";
        //node->printOne();
        //std::cout << " | distance : " << frontier->distance(node->getData()) << "\n\n";
        while (node->getData()==destination && (k<w || w<=0)) {
            if (!isDuplicate(node)) {
                node->print();
                std::vector<Node<Coordinate<int>>*> path;
                Node<Coordinate<int>>* p = node;
                while (p != nullptr) {
                    path.push_back(p);
                    p = p->parent;
                }
                
                std::reverse(path.begin(), path.end());
                this->allPaths.push_back(path);
                d = 0;
                k++;

                Coordinate<int> pos = node->getData();
                AI::blocks[pos.y][pos.x]++;
                this->explored.push_back(node);
            }
            d++;
            std::cout << k <<" Explored\n\n";
            //this->frontier->printOne();
            node = this->frontier->remove();
            //std::cout << "Best One : ";
            //node->printOne();
            //std::cout << " | distance : " << this->frontier->distance(node->getData()) << "\n\n";
        }
        Coordinate<int> pos = node->getData();
        AI::blocks[pos.y][pos.x]++;
        this->explored.push_back(node);
        AI::explore();
        std::vector<Coordinate<int>> neighb = AI::neighbours4(node->getData());
        for (int i=0; i<neighb.size(); i++) {
            if (!isExplored(neighb[i], node)) {
                Node<Coordinate<int>>* newNode = new Node(neighb[i], node);
                this->frontier->add(newNode);
            }
        }
    }
    if (this->weight>this->allPaths.size() || this->weight<=0)
        this->weight = this->allPaths.size();
}

void AI::search() {
    clearSearch();
    this->allSearch.push_back(position);
    AI::blocks[position.y][position.x]++;
    AI::explore();
    while (true) {
        int n = this->allSearch.size();
        this->position = this->allSearch[n-1];
        Coordinate<int> newPos = AI::bestPosition4(position);
        if (AI::blocks[newPos.y][newPos.x]>0 && AI::blocks[position.y][position.x]==1) {
            if (AI::allChecked()) break;
        }
        AI::blocks[newPos.y][newPos.x]++;
        this->explore();
        this->position = newPos;
        this->allSearch.push_back(newPos);
    }
}

void AI::multiSearch() {
    for (auto bot : AI::bots) {
        bot->allSearch.push_back(bot->position);
        AI::blocks[bot->position.y][bot->position.x]++;
        std::cout << "bot : " << bot << std::endl;
        AI::explore();
    }
    int b = true;
    while (b) {
        for (auto bot : AI::bots) {
            int n = bot->allSearch.size();
            bot->position = bot->allSearch[n-1];
            Coordinate<int> newPos = AI::bestPosition4(bot->position);
            if (AI::blocks[newPos.y][newPos.x]>0 && AI::blocks[bot->position.y][bot->position.x]>=1) {
                if (AI::allChecked()) {
                    b = false;
                    break;
                }
            }
            AI::blocks[newPos.y][newPos.x]++;
            std::cout << "bot : " << bot << std::endl;
            AI::explore();
            bot->position = newPos;
            bot->allSearch.push_back(newPos);
        }
    }
}

void AI::initFrontier()
{
    switch(AI::frontierType) {
        case 0:
            this->frontier = new StackFrontier<int>();
            break;
        case 1:
            this->frontier = new QueueFrontier<int>();
            break;
        case 2:
            this->frontier = new GreedyFrontier<int>(&this->destination, AI::dimensions);
            break;
        default:
            this->frontier = new AStarFrontier<int>(&this->destination, AI::dimensions);

    }
}