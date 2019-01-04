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

vector<Segment> filterNearX(const vector<Segment>& v, int x) {
    vector<Segment> ret;
    for(auto& segment : v)
        if (segment.a.x < x && segment.b.x > x || segment.b.x < x && segment.a.x > x)
            ret.push_back(segment);
        
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        //Polygon poly(n);
        Point prev, first;
        vector<Segment> segments;

        cin >> first.x >> first.y;
        n--;
        prev = first;
        
        //poly.addPoint(first);

        while(n--) {
            Point current;
            cin >> current.x >> current.y;
            //poly.addPoint(current);
            segments.push_back({prev, current});
            prev = current;
        }
        segments.push_back({prev, first});

        double threshold, x;
        cin >> threshold >> x;
        Line line({{x,0}, {x,10}});

        //cout << "Polygon: ";
        //poly.print(); cout << endl;
        //DEBUG(threshold);
        //DEBUG(x);

        vector<Segment> valid = filterNearX(segments, x);

        bool inside = false;
        double count = 0;
        vector<double> yIntsects;
        
        for(auto& segment : valid) {
            Point intsect = lineToSegmentIntersection(line, segment);
            yIntsects.push_back(intsect.y);
            //segment.print(); cout << " intersects at "; intsect.print(); cout << endl;
            
            //if (inside)
                //count += dist(prev, intsect);
            
            //prev = intsect;
            //inside = !inside;
        }
        
        std::sort(yIntsects.begin(), yIntsects.end());

        for(int i=0; i < yIntsects.size(); i++) {
            if (inside) 
                count += yIntsects[i] - yIntsects[i-1];
            inside = !inside;
        }

        //DEBUG(count);

        if (count + EPS > threshold)
            cout << "YES\n";
        else cout << "NO\n";

    }

    return 0;
}