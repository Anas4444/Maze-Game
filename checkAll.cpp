#include "checkAll.h"
#include <fstream>
#include <string>

template <class T, class V>
Maze<T, V>::Maze(std::string path) {
    num_explored = 0;
    std::string line;
    std::ifstream myfile(path);
    while (std::getline(myfile, line)) content.push_back(line);
    height = content.size();
    width = content[0].length();
    walls = new bool*[height];
    checked = new int*[height];
    for (int i=0; i<height; i++) {
        checked[i] = new int[width];
        walls[i] = new bool[width];
    }
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            checked[i][j] = 0;
            if (content[i][j] == 'A' || content[i][j] == 'B') {
                if (content[i][j] == 'A')
                    position = new Node<T, V>(std::make_tuple(i, j));
                walls[i][j] = false;
            }
            else if (content[i][j] == ' ') walls[i][j] = false;
            else walls[i][j] = true;
        }
    }
}

template <class T, class V>
void Maze<T, V>::print() {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (walls[i][j]) std::cout << '&';
            else if (i==std::get<0>(position->state) && j==std::get<1>(position->state)) std::cout << 'P';
            else if (checked[i][j]>0) std::cout << '*';
            else std::cout << ' ';
        }
        std::cout << '\n';
    }
}

template <class T, class V>
std::tuple<T, V> Maze<T, V>::theBestNeighbor(const T& state) {
    int row = std::get<0>(state);
    int col = std::get<1>(state);
    std::vector<std::tuple<T, V>> condidates;
    condidates.push_back(std::make_tuple(std::make_tuple(row-1, col), "up"));
    condidates.push_back(std::make_tuple(std::make_tuple(row+1, col), "down"));
    condidates.push_back(std::make_tuple(std::make_tuple(row, col-1), "left"));
    condidates.push_back(std::make_tuple(std::make_tuple(row, col+1), "right"));

    std::tuple<T, V> bestNeighbor;
    int i = 0;
    for (; i<condidates.size(); i++) {
        T s = std::get<0>(condidates[i]);
        V action = std::get<1>(condidates[i]);
        int r = std::get<0>(s);
        int c = std::get<1>(s);
        if (r >= 0 && r < height && c >= 0 && c < width && !walls[r][c]) {
            bestNeighbor = std::make_tuple(std::make_tuple(r, c), action);
            break;
        }
    }
    for (; i<condidates.size(); i++) {
        T s = std::get<0>(condidates[i]);
        V action = std::get<1>(condidates[i]);
        int r = std::get<0>(s);
        int c = std::get<1>(s);
        if (r >= 0 && r < height && c >= 0 && c < width && !walls[r][c]) {
            T coordinates = std::get<0>(bestNeighbor);
            if (checked[r][c] < checked[std::get<0>(coordinates)][std::get<1>(coordinates)]) bestNeighbor = std::make_tuple(std::make_tuple(r, c), action);
        }
    }
    return bestNeighbor;
}

template <class T, class V>
bool Maze<T, V>::allStatesChecked() {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (checked[i][j]==0 && !walls[i][j]) return false;
        }
    }
    return true;
}

template <class T, class V>
void Maze<T, V>::solve() {
    checked[std::get<0>(position->state)][std::get<1>(position->state)]++;
    while(true) {
        num_explored++;
        std::tuple<T, V> neighbor = theBestNeighbor(position->state);
        T state = std::get<0>(neighbor);
        V action = std::get<1>(neighbor);
        if (checked[std::get<0>(state)][std::get<1>(state)]>0 && checked[std::get<0>(position->state)][std::get<1>(position->state)]==1) {
            if (allStatesChecked()) break;
        }
        checked[std::get<0>(state)][std::get<1>(state)]++;
        position->setNode(state, action);
    }
}