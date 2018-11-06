#include <iostream>
#include <climits>

#define DEBUG(x) cout << #x ": " << x << endl;

using namespace std;

// UVA 108 - Maximum Sum
// Use kadane's algorithm adjusted for 2D to find
// the maximum submatrix

int main() {    
    int n;
    
    while(cin >> n) {
        int v[n+1][n+1];
        int ac[n+1][n+1];

        for(int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                ac[i][j] = 0;

        
        for(int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> v[i][j];
            }
        }

        int ans = INT_MIN;
        int sum[n+1];
        
        for(int startRow = 1; startRow <= n; startRow++) {
            for(int i = 0; i <=n; i++)
                sum[i] = 0;

            for(int endRow = startRow; endRow <= n; endRow++) {
                int max_row = 0;
                int max_sum = INT_MIN;
                
                for(int col = 1; col <= n; col++) {
                    sum[col] += v[endRow][col];
                    max_row = std::max(0, max_row+sum[col]);
                    max_sum = std::max(max_sum, max_row);
                }
                ans = std::max(ans, max_sum);
            }
        }

        cout << ans << endl;
    }
    return 0;
}