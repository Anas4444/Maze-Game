#include <iostream>

template <class S>
struct Coordinate {
    S x, y, z;
    Coordinate() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Coordinate(S x, S y) {
        this->x = x;
        this->y = y;
        this->z = 0;
    }
    Coordinate(S x, S y, S z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void set(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    ~Coordinate() {}

    int operator==(Coordinate<S> const &m) const { 
        return (x==m.x && y==m.y && z==m.z);
    }

    int operator!=(Coordinate<S> const &m) const { 
        return (x!=m.x || y!=m.y || z!=m.z);
    }

    int operator<=(Coordinate<S> const &m) const {
        return (x<=m.x && y<=m.y && z<=m.z);
    }

    int operator>=(Coordinate<S> const &m) const {
        return (x>=m.x && y>=m.y && z>=m.z);
    }
};

template <class S>
std::ostream &operator<<(std::ostream &os, Coordinate<S> const &m) { 
    return os << "(" << m.x << ", " << m.y << ", " << m.z << ")";
}