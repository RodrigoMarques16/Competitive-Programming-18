#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define EPS 1e-6
#define N 10005

using namespace std;

const double INF = numeric_limits<double>::max();

// UVA 10245 - The Closest Pair Problem
// 
// Apply closest point algorithm based on divide and conquer
// Divide the field in two and find the closest pair in each side recursively
// Complexity is in the merge algorithm
//
// could be optimized by ordering points by y when merging
// and all the square roots are probably inflating the run time

struct Point {
    double x, y;

    explicit Point() : x(), y() {
    }

    Point(const double& _x, const double& _y) : x(_x), y(_y) {
    }

    bool operator!=(const Point& other){
        return this->x != other.x && this->y != other.y;
    }

    Point operator-(const Point& other) const {
        return Point(this->x - other.x, this->y - other.y);
    }

    void print() {
        cout << "(" << this->x << "," << this->y << ")";
    }

    static bool cmp(const Point& a, const Point& b) {
        if (a.x == b.x) 
            return a.y < b.y;
        return a.x < b.x;
    }

    static bool xCmp(const Point& a, const Point& b) {
        return a.x < b.x;
    }

    static bool yCmp(const Point& a, const Point& b) {
        return a.y < b.y;
    }

};

double dist(const Point& A, const Point& B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double merge(const vector<Point>& points, int low, int mid, int high, double min_dist) {
    double mid_x = points[mid].x;

    // Iterate through all points from the center to the left
    for(int i = mid; i >= low; i--) {
        
        // Break when we the distance to the center is larger than min_dist
        // (points are ordered)
		if ((points[i].x - mid_x) >= min_dist)
            break;
		
        // Iterate through all points from the center to the right
        for(int j = mid+1; j <= high; j++) {

            // Break when we get too far from the left point
			if ((points[i].x - points[j].x) >= min_dist)
                break;
            
            min_dist = std::min(min_dist, dist(points[i], points[j]));
		}
	}

    return min_dist;
}

double solve(const vector<Point>& points, int low, int high) {
    if (low >= high)
        return INF;
    
    if (low == high - 1) 
        return dist(points[low], points[high]);
    
    int mid = low + (high - low) / 2;
    
    double min_dist = INF;
    min_dist = std::min(min_dist, solve(points, low, mid));
    min_dist = std::min(min_dist, solve(points, mid+1, high));
    min_dist = std::min(min_dist, merge(points, low, mid, high, min_dist));

    return min_dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n; 

    while(cin >> n, n != 0) {
        vector<Point> points(n);

        for(int i=0; i < n; i++)
            cin >> points[i].x >> points[i].y;
        
        // Sort points by x
        std::sort(points.begin(), points.end(), Point::xCmp);

        double min_dist = solve(points, 0, n-1);
        if (min_dist >= 10000)
            cout << "INFINITY\n";
        else cout << fixed 
                  << setprecision(4) 
                  << min_dist 
                  << endl;
    }
    return 0;
}