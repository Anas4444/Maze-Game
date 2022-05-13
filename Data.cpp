#include <iostream>
#include <vector>
#include <string>

struct Data {
    std::vector<std::string> positions;
    int time;
    Data() {
        this->time=0;
    }
    Data(int time) {
        this->time = time;
    }
    Data(int time, std::vector<std::string> pos) {
        this->time = time;
        for (int i=0; i<pos.size(); i++)
            this->positions.push_back(pos[i]);
    }
    void set(int time, std::vector<std::string> pos) {
        this->time = time;
        for (int i=0; i<pos.size(); i++)
            this->positions.push_back(pos[i]);
    }
    ~Data() {
        this->positions.clear();
    }

    int operator==(Data const &m) const { 
        return (this->time==m.time);
    }

    int operator!=(Data const &m) const { 
        return (this->time!=m.time);
    }

    int operator<=(Data const &m) const {
        return (this->time<=m.time);
    }

    int operator>=(Data const &m) const {
        return (this->time>=m.time);
    }
};

std::ostream &operator<<(std::ostream &os, Data const &m) { 
    return os << m.time;
}

