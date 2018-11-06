#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 1005
#define K 1000005

using namespace std;

// SPOJ MSE06H - Japan
// Using a bit tree
// Start by sorting the bridges
// Then for every bridge we count the number of bridges 
// between it and the last position (range query)
// Build the tree as we go so we don't repeat intersections

typedef struct _Bridge {
    int east;
    int west;
} Bridge;

bool cmp(const Bridge& a, const Bridge& b) {
    if (a.east == b.east)
        return a.west < b.west;
    return a.east < b.east;
}

Bridge v[K];
int bt[N];

long long getSum(int index) {
    long long int sum = 0;
    while(index > 0) {
        sum += bt[index];
        index -= index & -index;
    }
    return sum;
}

void update(int n, int index, int val) {
    while(index <= n) {
        bt[index] += val;
        index += index & -index;
    }
}

void build(int n) {
    for(int i = 1; i <= n; i++) {
        bt[i] = 0;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for(int test = 1; test <= t; test++) {
        int n, m, k;

        scanf("%d%d%d", &n, &m, &k);

        for(int i = 0; i < k; i++) {
            int east, west;
            scanf("%d%d", &v[i].east, &v[i].west);
        }

        std::sort(v, v+k, cmp);

        build(m);

        long long sum = 0;
        for (int i = 0; i < k; i++) {
            update(m, v[i].west, 1);
            for(int i = 1; i <=m; i++)
                cout << bt[i] << " ";
            cout << endl;
            sum += getSum(m) - getSum(v[i].west);
        }

        printf("Test case %d: %lld\n", test, sum);
    }

    return 0;
}