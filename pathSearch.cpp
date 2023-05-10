#include "pathSearch.h"
#include <algorithm>
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
    for (int i=0; i<height; i++) walls[i] = new bool[width];
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (content[i][j] == 'A') {
                start = std::make_tuple(i, j);
                walls[i][j] = false;
            }
            else if (content[i][j] == 'B') {
                goal = std::make_tuple(i, j);
                walls[i][j] = false;
            }
            else if (content[i][j] == ' ') walls[i][j] = false;
            else walls[i][j] = true;
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
    for (int i=0; i<explored.size(); i++) {
        if (explored[i] == state) return true;
    }
    return false;
}

template <class T, class V>
void Maze<T, V>::print() {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (walls[i][j]) {
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
std::vector<std::tuple<V, T>> Maze<T, V>::neighbors(const T& state) {
    int row = std::get<0>(state);
    int col = std::get<1>(state);
    std::vector<std::tuple<V, T>> condidates;
    condidates.push_back(std::make_tuple("up", std::make_tuple(row-1, col)));
    condidates.push_back(std::make_tuple("down", std::make_tuple(row+1, col)));
    condidates.push_back(std::make_tuple("left", std::make_tuple(row, col-1)));
    condidates.push_back(std::make_tuple("right", std::make_tuple(row, col+1)));

    std::vector<std::tuple<V, T>> result;
    for (int i=0; i<condidates.size(); i++) {
        T s = std::get<1>(condidates[i]);
        V action = std::get<0>(condidates[i]);
        int r = std::get<0>(s);
        int c = std::get<1>(s);
        if (r >= 0 && r < height && c >= 0 && c < width && !walls[r][c]) result.push_back(std::make_tuple(action, std::make_tuple(r, c)));
    }
    return result;
}

template <class T, class V>
void Maze<T, V>::solve() {
    Node<T, V>* first = new Node<T, V>(start);
    QueueFrontier<T, V>* frontier = new QueueFrontier<T, V>();
    frontier->add(start);

    while(true) {
        if (frontier->empty()) return;
        Node<T, V>* node = frontier->remove();
        num_explored++;
        if (node->state == goal) {
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
                Node<T, V>* nod = new Node<T, V>(cells[i], actions[i]);
                solution.push_back(nod);
            }
            return;
        }
        explored.push_back(node->state);
        std::vector<std::tuple<V, T>> neighbor = neighbors(node->state);
        for (int i=0; i<neighbor.size(); i++) {
            T state = std::get<1>(neighbor[i]);
            V action = std::get<0>(neighbor[i]);
            if (!frontier->containsState(state) && !stateExplored(state)) {
                Node<T, V>* nod = new Node<T, V>(state, node, action);
                frontier->add(*nod);
            }
        }
    }
}