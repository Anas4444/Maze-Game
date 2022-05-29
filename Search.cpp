#include "Search.h"
#include <string>

template <class T, class V>
Maze<T, V>::Maze(std::string path) {
    num_explored = 0;
    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    V file = FPaths::ProjectConfigDir();
    file.Append("maze1.txt");
    //file = FString::Printf(TEXT("%s%s"), *file, &path);

    V FileContent;
    if (FileManager.FileExists(*file)) {
        FFileHelper::LoadFileToString(FileContent, *file); 
        V line1;
        while (FileContent.Split(TEXT("\n"), &line1, &FileContent)) { content.push_back(line1); }
        content.push_back(FileContent);
        height = content.size();
        width = content[0].Len()-1;
        for (int i=0; i<content.size(); i++) {
            UE_LOG(LogTemp, Warning, TEXT("%s"), *content[i]);
        }
        UE_LOG(LogTemp, Warning, TEXT("(%d, %d)"), height, width);
        explored = new int*[height];
        for (int i=0; i<height; i++) {
            explored[i] = new int[width];
        }
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                FString currChar = content[i].Mid(j, 1);
                if (currChar.Equals(TEXT("A"))) {
                    start = new NodeS<T, V>(std::make_tuple(i, j));
                    explored[i][j] = 1;
                } 
                else if (currChar.Equals(TEXT("B"))) {
                    explored[i][j] = 0;
                    goal = new NodeS<T, V>(std::make_tuple(i, j));
                }
                else if (currChar.Equals(TEXT(" "))) {
                    explored[i][j] = 0;
                }
                else {
                    explored[i][j] = -1;
                    UE_LOG(LogTemp, Warning, TEXT("%d"), explored[i][j]);
                }
            }
        }
    }
}

template <class T, class V>
bool Maze<T, V>::ijInSolution(int i, int j) {
    T s = std::make_tuple(i, j);
    for (int k=0; k<solution.size(); k++) {
        if (solution[k]->state == s) return true;
    }
    return false;
}

template <class T, class V>
bool Maze<T, V>::stateExplored(const T& state) {
    if (explored[std::get<0>(state)][std::get<1>(state)]>0) return true;
    return false;
}

template <class T, class V>
void Maze<T, V>::print() {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (explored[i][j] == -1) {
                std::cout << '&';
                }
            else if (i==std::get<0>(start) && j==std::get<1>(start)) std::cout << 'A';
            else if (i==std::get<0>(goal) && j==std::get<1>(goal)) std::cout << 'B';
            else if (ijInSolution(i, j)) std::cout << '*';
            else std::cout << ' ';
        }
        std::cout << '\n';
    }
}

template <class T, class V>
std::vector<std::tuple<T, V>> Maze<T, V>::Neighbors(const T& state) {
    int row = std::get<0>(state);
    int col = std::get<1>(state);
    std::vector<std::tuple<T, V>> condidates;
    condidates.push_back(std::make_tuple(std::make_tuple(row-1, col), "up"));
    condidates.push_back(std::make_tuple(std::make_tuple(row+1, col), "down"));
    condidates.push_back(std::make_tuple(std::make_tuple(row, col-1), "left"));
    condidates.push_back(std::make_tuple(std::make_tuple(row, col+1), "right"));

    std::vector<std::tuple<T, V>> result;
    for (int i=0; i<condidates.size(); i++) {
        T s = std::get<0>(condidates[i]);
        V action = std::get<1>(condidates[i]);
        int r = std::get<0>(s);
        int c = std::get<1>(s);
        if (r >= 0 && r < height && c >= 0 && c < width && explored[r][c]>-1) result.push_back(std::make_tuple(std::make_tuple(r, c), action));
    }
    return result;
}

template <class T, class V>
std::tuple<T, V> Maze<T, V>::theBestNeighbor(const T& s) {
    int row = std::get<0>(s);
    int col = std::get<1>(s);
    std::vector<std::tuple<T, V>> condidates;
    condidates.push_back(std::make_tuple(std::make_tuple(row-1, col), "up"));
    condidates.push_back(std::make_tuple(std::make_tuple(row+1, col), "down"));
    condidates.push_back(std::make_tuple(std::make_tuple(row, col-1), "left"));
    condidates.push_back(std::make_tuple(std::make_tuple(row, col+1), "right"));

    std::tuple<T, V> bestNeighbor;
    int i = 0;
    for (; i<condidates.size(); i++) {
        T state = std::get<0>(condidates[i]);
        V action = std::get<1>(condidates[i]);
        int r = std::get<0>(state);
        int c = std::get<1>(state);
        if (r >= 0 && r < height && c >= 0 && c < width && explored[r][c]>-1) {
            bestNeighbor = std::make_tuple(state, action);
            break;
        }
    }
    for (; i<condidates.size(); i++) {
        T state = std::get<0>(condidates[i]);
        V action = std::get<1>(condidates[i]);
        int r = std::get<0>(state);
        int c = std::get<1>(state);
        if (r >= 0 && r < height && c >= 0 && c < width && explored[r][c]>-1) {
            T coordinates = std::get<0>(bestNeighbor);
            if (explored[r][c] < explored[std::get<0>(coordinates)][std::get<1>(coordinates)]) {
                if (solution.size()>1) {
                    if (solution[solution.size()-2]->state != state)
                        bestNeighbor = std::make_tuple(state, action);
                }
                else bestNeighbor = std::make_tuple(state, action);
            }
            else if (solution.size()>1) {
                if (solution[solution.size()-2]->state == coordinates) bestNeighbor = std::make_tuple(state, action);
            }
        }
    }
    return bestNeighbor;
}

template<class T, class V>
void Maze<T, V>::reset(NodeS<T, V>& g)
{
    num_explored = 0;
    start->setNode(solution[solution.size()-1]->state);
    goal->setNode(g);
    solution.empty();
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (explored[i][j]>-1) explored[i][j] = 0;
        }
    }
}

template <class T, class V>
bool Maze<T, V>::allStatesExplored() { 
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (explored[i][j]>0) {
                std::vector<std::tuple<T, V>> neighbor = Neighbors(std::make_tuple(i, j));
                for (int k=0; k<neighbor.size(); k++) {
                    T state = std::get<0>(neighbor[k]);
                    if (explored[std::get<0>(state)][std::get<1>(state)] == 0) return false;
                } 
            }
        }
    }
    return true;
}

template <class T, class V>
void Maze<T, V>::checkAll() {
    explored[std::get<0>(start->state)][std::get<1>(start->state)]++;
    solution.push_back(new NodeS<T, V>(start->state, start->action));
    while(true) {
        num_explored++;
        std::tuple<T, V> neighbor = theBestNeighbor(solution[solution.size()-1]->state);
        T state = std::get<0>(neighbor);
        V action = std::get<1>(neighbor);
        if (explored[std::get<0>(state)][std::get<1>(state)]>0 && explored[std::get<0>(solution[solution.size()-1]->state)][std::get<1>(solution[solution.size()-1]->state)]==1) {
            if (allStatesExplored()) break;
        }
        explored[std::get<0>(state)][std::get<1>(state)]++;
        solution.push_back(new NodeS<T, V>(state, action));
    }
}

template <class T, class V>
void Maze<T, V>::solve() {
    NodeS<T, V>* first = new NodeS<T, V>(*start);
    QueueFrontier<T, V>* frontier = new QueueFrontier<T, V>();
    frontier->add(*start);

    while(true) {
        if (frontier->empty()) return;
        NodeS<T, V>* node = frontier->remove();
        num_explored++;
        if (node->state == goal->state) {
            std::vector<V> actions;
            std::vector<T> cells;
            while(node->parent) {
                actions.push_back(node->action);
                cells.push_back(node->state);
                node = node->parent;
            }
            std::reverse(actions.begin(), actions.end());
            std::reverse(cells.begin(), cells.end());
            for (int i=0; i<actions.size(); i++) {
                NodeS<T, V>* nod = new NodeS<T, V>(cells[i], actions[i]);
                solution.push_back(nod);
            }
            return;
        }
        explored[std::get<0>(node->state)][std::get<1>(node->state)]++;
        std::vector<std::tuple<T, V>> neighbor = Neighbors(node->state);
        for (int i=0; i<neighbor.size(); i++) {
            T state = std::get<0>(neighbor[i]);
            V action = std::get<1>(neighbor[i]);
            if (!frontier->containsState(state) && !stateExplored(state)) {
                NodeS<T, V>* nod = new NodeS<T, V>(state, node, action);
                frontier->add(*nod);
            }
        }
    }
}