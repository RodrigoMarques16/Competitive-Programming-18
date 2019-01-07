#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

#define DEBUG(x) cout << #x << ": " << x << endl;

using namespace std;

const double EPS = 1e-6;
const double INF = numeric_limits<double>::max();

struct Point {
    double x, y;

    explicit Point() : x(), y() {
    }

    Point(const double& _x, const double& _y) : x(_x), y(_y) {
    }

    bool operator!=(const Point& other){
        return this->x != other.x && this->y != other.y;
    }

    Point operator - (const Point& other) const {
        return Point(this->x - other.x, this->y - other.y);
    }

    static bool xCmp(const Point& a, const Point& b) {
        return a.x > b.x;
    }

    static bool yCmp(const Point& a, const Point& b) {
        return a.y > b.y;
    }

    void print() {
        cout << this->x << " " << this->y;
    }
};

struct Segment {
    Point a;
    Point b;

    explicit Segment() : a(), b() {
    }

    Segment(const Point& _a, const Point& _b) : 
        a(_a), b(_b) {
    }

    void print() {
        this->a.print();
        cout << " to ";
        this->b.print();
    }
};

struct Line {
    double a;
    double b;
    double c;

    explicit Line() : a(0), b(0), c(0) {
    }

    Line(const Point& A, const Point& B) {
        this->a = +(B.y - A.y);
        this->b = -(B.x - A.x);
        this->c = -A.x * B.y + B.x * A.y;
    }
};

double dist(const Point& A, const Point& B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double modul(double a) {
    if (a > EPS)
        return a;
    else
        return -a;
}

double CCW(const Point& A, const Point& B, const Point& C) {
    return (C.x - A.x) * (B.y - A.y) - (C.y - A.y) * (B.x - A.x);
}

bool onSegment(const Segment& S, const Point& P) {
    if (modul(CCW(S.a, S.b, P)) > EPS)
        return false; /// not collinear

    if ( !(min(S.a.x, S.b.x) <= P.x && P.x <= max(S.a.x, S.b.x)) )
        return false;

    if ( !(min(S.a.y, S.b.y) <= P.y && P.y <= max(S.a.y, S.b.y)) )
        return false;

    return true;
}

Point lineToLineIntersection(const Line& A, const Line& B) {
    double det = A.a * B.b - A.b * B.a;

    if (modul(det) < EPS) /// det == 0
        return Point(INF, INF); /// no intersection
    else
    {
        double x = -(A.c * B.b - A.b * B.c) / det;
        double y = -(A.a * B.c - A.c * B.a) / det;

        return Point(x, y);
    }
}

Point lineToSegmentIntersection(const Line& A, const Segment& S) {
    Point I = lineToLineIntersection(A, Line(S.a, S.b));

    /// check if I exists and is on segment
    if (I != Point(INF, INF) && onSegment(S, I))
        return I;
    else
        return Point(INF, INF); /// no intersection
}

struct Polygon {
    int n;
    vector<Point> points;

    explicit Polygon() : n(), points() {
    }

    Polygon(const int& _n) : n(_n) {
    }

    Polygon(const int& _n, const vector<Point>& _points) : 
        n(_n), points(_points) {
    }

    void addPoint(const Point& point) {
        points.push_back(point);
    }

    void print() {
        for(auto& point : points){
            point.print();
            cout << ", ";
        }
    }
};

double cross(Point v, Point w) {
    return v.x*w.y - v.y*w.x;
}

double orient(Point a, Point b, Point c) { 
    return cross(b-a,c-a);
}

bool isConvex(vector<Point> p) {
    bool hasPos=false, hasNeg=false;
    for (int i=0, n=p.size(); i<n; i++) {
        int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

int main() {
    int n;

    while(cin >> n, n != 0) {
        vector<Point> gallery;
        while(n--) {
            Point p;
            cin >> p.x >> p.y;
            gallery.push_back(p);
        }
        isConvex(gallery) ? cout << "No\n" : cout << "Yes\n"; 
    }

    return 0;
}