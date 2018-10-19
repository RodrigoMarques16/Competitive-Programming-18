#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int buy(int k, vector<int> objects) {

    for(int i = 0; i < (int) objects.size(); i++) {
        objects[i] += (i+1)*k;
    }
    sort(objects.begin(), objects.end());   
    int cost = 0;
    for(int i = 0; i < k; i++) {
        cost += objects[i];
    }
    return cost;
}


int search(int low, int high, vector<int> &objects, int budget) {
    int middle = low + (high-low) / 2;

    if (buy(low, objects) > budget) {
        cout << low-1 << " " << buy(low-1, objects) << endl;
        return 0;
    }
    if (low == high-1) {
        cout << low << " " << buy(low, objects) << endl;
        return 0;
    }

    if (buy(middle, objects) <= budget) {
        return search(middle, high, objects, budget);
    } else {
        return search(low, middle, objects, budget);
    }
}

int main() {

    int n, budget;
    vector<int> objects;

    cin >> n >> budget;

    for(int i=1; i <= n; i++) {
        int p;
        cin >> p;
        objects.push_back(p);
    }

    search(0, n+1, objects, budget);
}