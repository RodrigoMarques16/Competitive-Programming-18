#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

#define DEBUG(x) cout << #x << ": " << x << endl;

using namespace std;

const double EPS = 1e-10;

struct Point {
    double x, y;

    explicit Point() : x(), y() {
    }

    Point(const double& _x, const double& _y) : x(_x), y(_y) {
    }

    bool operator!=(const Point& other){
        return this->x != other.x && this->y != other.y;
    }

    static bool cmp(const Point& a, const Point& b) {
        return a.x > b.x;
    }

    void print() {
        cout << this->x << " " << this->y;
    }
};

double dist(const Point& A, const Point& B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int t;
    cin >> t;

    vector<Point> mountainRange;

    while(t--) {
        int n;
        cin >> n;

        //cout << "\nTEST CASE\n";

        mountainRange.clear();

        while(n--) {
            double x, y;
            cin >> x >> y;
            mountainRange.push_back({x,y});
        }

        sort(mountainRange.begin(), mountainRange.end(), Point::cmp);

        //cout << "Peaks:\n";
        //for (auto& peak : mountainRange)
        //    cout << peak.x << " " << peak.y << endl;
        //cout << endl;

        Point prev = *(mountainRange.begin());
        double length = 0;
    
        //cout << "Distances:\n";
        for(int i=1; i < mountainRange.size(); i++) {
            if (mountainRange[i].y > prev.y) {
                Point top  = mountainRange[i];
                Point base = mountainRange[i-1];

                double ratio = (top.y - prev.y) / (top.y - base.y);
                length += dist(top,base) * ratio;

                //base.print(); cout << " to "; top.print(); cout << " :";
                //cout << dist(base, top); cout << endl;

                //intsect.print(); cout << " to "; top.print(); cout << " :";
                //cout << dist(intsect, top); cout << endl;

                prev = mountainRange[i];
            }
        }
        cout << setprecision(2) << fixed << length << endl;
    }

    

    return 0;
}