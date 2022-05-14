#include <iostream>

template <class S>
struct Pair {
    S x, y;
    Pair() {
        this->x=0;
        this->y=0;
    }
    Pair(S x, S y) {
        this->x = x;
        this->y = y;
    }
    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
    ~Pair() {}

    int operator==(Pair<S> const &m) const { 
        return (x==m.x && y==m.y);
    }

    int operator!=(Pair<S> const &m) const { 
        return (x!=m.x || y!=m.y);
    }

    int operator<=(Pair<S> const &m) const {
        return (x<=m.x && y<=m.y);
    }

    int operator>=(Pair<S> const &m) const {
        return (x>=m.x && y>=m.y);
    }
};

template <class S>
std::ostream &operator<<(std::ostream &os, Pair<S> const &m) { 
    return os << "(" << m.x << ", " << m.y << ")";
}