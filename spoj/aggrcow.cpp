#include <iostream>
#include <vector>
#include <algorithm>
 
#define DEBUG(x) cout << #x << ": " << x << endl;

using namespace std;

// AGGRCOW - Aggressive cows
// Given n stalls and their positions, find the best
// way to fill them for the largest minimum distance
//
// Using binary search on the distance
// The search function checks how many cows can fit in
// for a given minimum distance and returns true if 
// that number is equal or higher than required
//
// Time:  O(n log n) (sorting)
// Space: O(n)

bool search(int min_dist, vector<int> stalls, int c) {
    int first, cows = 1;
    first = stalls[0];

    for(int i = 1; i < stalls.size(); i++) {
        // Ignore stalls under minimum distance
        if (stalls[i] - first >= min_dist) {
            first = stalls[i];
            cows++;
        }
    }

    return (cows >= c);
}

int main() {

    int t;

    cin >> t;

    while(t--) {
        int n, c;
        vector<int> stalls;
        
        cin >> n >> c;
        int dist = n, high=0, low = 0;

        while(n--) {
            int i;
            cin >> i;
            stalls.push_back(i);
            high = max(high, i);
        }
        
        // Stalls positions aren't given in order

        sort(stalls.begin(), stalls.end());

        while(low < high) {
            int middle = low + (high - low) / 2;

            if (search(middle, stalls, c)) {
                low = middle + 1;
            } else {
                high = middle;
            }
            
            if (search(low, stalls, c) == false){
                cout << middle << endl;
                break;
            }
        }
    }

}

