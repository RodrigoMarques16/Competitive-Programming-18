#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 100005

using namespace std;

// SPOJ UPDATEIT - Update the Array
// Use a binary index tree to track the values 
// summed to the array

int v[N];
int bt[N];

long long query(int index) {
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

void range_update(int n, int left, int right, int val) {
    // add val to every index > left
    update(n, left, val);
    // subtract val from every index > right
    update(n, right+1, -val);
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
        int n, u;
        scanf("%d%d", &n, &u);        
        
        build(n+1);

        while(u--) {
            int l, r, val;
            scanf("%d%d%d", &l, &r, &val);
            range_update(n, l+1, r+1, val);
        }

        int q;
        scanf("%d", &q);
        while(q--) {
            int qq;
            scanf("%d", &qq);
            cout << query(qq+1) << endl;
        }
    }

    return 0;
}