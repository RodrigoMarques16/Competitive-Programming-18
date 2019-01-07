#include <iostream>

#define DEBUG(x) cout << #x << ": " << x << endl;

struct Point {
    double x, y;

    explicit Point() : x(), y() {
    }

    Point(const double& _x, const double& _y) : x(_x), y(_y) {
    }

    bool operator!=(const Point& other){
        return this->x != other.x && this->y != other.y;
    }

    void print() {
        std::cout << this->x << " " << this->y;
    }
};

int main() {
    Point p = Point();
    p.print();

    return 0;
}