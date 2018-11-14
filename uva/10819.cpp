#include <iostream>
#include <cstring>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 105
#define M 10500
#define INF -1e10

using namespace std;

// UVA 10819 - Trouble of 13-Dots
//
// For each item iterate down from the maximum 
// spendable money to 0 and save the maximum favour for
// possible values in an array.
//
// Time:  O(N*M)
// Space: O(M)

int main() {
    int m, n, mtotal;
    int best[M];

    while (cin >> m >> n) {
        std::fill(best, best+M, -1);
        best[0] = 0;

        mtotal = m;
        if (m > 1800) 
            mtotal += 200;

        for (int i = 0; i < n; i++) {
            int p, v;
            cin >> p >> v;

            for (int j = mtotal - p; j >= 0; j--) {
                // Can't spend this much (yet)
                if (best[j] == -1) continue;
                // Else compare it to the memo
                best[j+p] = std::max(best[j+p], best[j] + v);
                
                //cout << j+p << ":" << best[j+p] << ", " << best[j] + v << " | ";
            }
            //cout << endl;
        }
        
        int answer = 0;
        for (int i = 0; i <= mtotal; i++) {
            // Ignore cases where the discount doesn't apply
            if (m < i && i <= 2000) continue;
            answer = max(answer, best[i]);
        }

        cout << answer << endl;
    }
}