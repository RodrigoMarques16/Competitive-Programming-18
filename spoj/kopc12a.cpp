#include <iostream>
#include <functional> 
#include <vector> 

#define DEBUG(x) cout << #x ": " << x << endl;

using namespace std;

// KOPC12A - K12 - Building Construction
// https://www.spoj.com/problems/KOPC12A/
//
// Given n buildings made of bricks with different 
// heights, find what height they can all be set to
// so that the reconstruction cost is minimum

// Using binary search on the height of the buildings
//
// The calcCost function calculates the cost of setting 
// all buildings to a specific height

typedef std::function<long long(int)> eval;
 
vector<int> height;
vector<int> cost;

long long calcCost(int h) {
    long long c = 0;
    for(int i = 0; i < height.size(); i++) {
        c += cost[i] * abs(h - height[i]);
    }
    return c;
}

int ternary_search(eval f, int low, int high) {
    if (high == low)
        return low;

    int m1 = low  + (high-low) / 3;
    int m2 = high - (high-low) / 3;

    if (f(m1) > f(m2)) 
        return ternary_search(f, m1+1, high);
    else
        return ternary_search(f, low, m2-1);
}

int main() {

    int t;
    cin >> t;

    while(t--) {
        int n, x, max_height = 0;

        height.clear();
        cost.clear();

        cin >> n;

        for(int i=0; i < n; i++) {
            cin >> x;
            max_height = max(max_height, x);
            height.push_back(x); 
        }
        for(int i=0; i < n; i++) {
            cin >> x;
            cost.push_back(x); 
        }
        
        cout << calcCost(ternary_search(calcCost, 0, 10000))
             << endl;

    }

    return 0;

}