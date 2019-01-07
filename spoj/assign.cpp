#include <iostream>
#include <bitset>
#include <array> 

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 25

using namespace std;

// SPOJ ASSIGN - Assignments

// Bitmask DP

typedef array<int, N> student;
int n;
array<student, N> students;
array<long long, (1<<20)+5> dp;

long long solve(int idx, int mask) {
    
    if (idx == n)       return 1;
    if (dp[mask] != -1) return dp[mask];

    long long count = 0;
    for(int i = 0; i < n; i++) {
        // Test the bit at position 'i'
        bool taken = (mask >> i) & 1;
        if (!taken & students[idx][i]) {
            // Set the bit at position 'i' to
            count += solve(idx+1, (mask | 1 << i));
        }
    }
    dp[mask] = count;
    return count;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int t; 
    cin >> t;

    while(t--) {
        cin >> n;

        dp.fill(-1);

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                cin >> students[i][j];
            }
        }
        cout << solve(0, 0) << endl;
    }
 
    return 0;
}