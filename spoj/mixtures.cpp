#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 100

using namespace std;

int color[N];

int mix[N][N];   // mix[i][j] = Value obtained from mixing
                 // the elements from v[i] to v[j]

int smoke[N][N]; // smoke[i][j] = Minimum smoke possible
                 // from mixing elements i to j

// SPOJ MIXTURES - Mixtures
//  

int solve(int i, int j) {
    if (i == j)   return 0;
    if (i+1 == j) return color[i] * color[j];

    int& ref = smoke[i][j];
    if (ref == INT_MAX) {
        for(int k = i; k < j; k++) {
            int count = mix[i][k] * mix[k+1][j]
                      + solve(i, k)
                      + solve(k+1, j);
            ref = std::min(ref, count);
        }
    }

    return ref;
}

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &color[i]);
            mix[i][i] = color[i];
        }
        
        // Pre-calc all the mixes
        for(int i = 0; i < n;++i){
            for(int j = i+1; j < n;++j){
                mix[i][j] = (mix[i][j-1] + color[j]) % 100;
            }
        }

        // Initialize smoke to infinity
        for(int i = 0;i < n;++i){
            for(int j = 0;j < n;++j){
                smoke[i][j] = INT_MAX;
                printf("%3d ", mix[i][j]);
            }
            printf("\n");
        }

        printf("%d\n", solve(0, n-1));
    }

    return 0;
}