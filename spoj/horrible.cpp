#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 1e7+5

using namespace std;

// SPOJ HORRIBLE - Horrible Queries
// Binary index tree with range update and range query
// Two bit's are needed to answer the range queries

int v[N];
long long bt1[N];
long long bt2[N];

long long query(long long *v, int index) {
    long long int sum = 0;
    while(index > 0) {
        sum += v[index];
        index -= index & -index;
    }
    return sum;
}

long long query(int index) {
    return query(bt1, index) * index 
         - query(bt2, index);
}

long long range_query(int left, int right) {
    return query(right) - query(left-1);
}

void update(long long *v, int n, int index, long long val) {
    while(index <= n) {
        v[index] += val;
        index += index & -index;
    }
}

void range_update(int n, int left, int right, long long val) {
    // add val to every index > left
    update(bt1, n, left, val);
    // subtract val from every index > right
    update(bt1, n, right+1, -val);
    
    update(bt2, n, left, val*(left-1));
    update(bt2, n, right+1, -val*right);
}



void build(int n) {
    for(int i = 1; i <= n; i++) {
        bt1[i] = bt2[i] = 0;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for(int test = 1; test <= t; test++) {
        int n, c;
        scanf("%d%d", &n);        
        
        while(n--) {
            int x, y, value;
            scanf("%d%d%d", &x, &y, &value)
        }

        build(n+1);

        while(c--) {
            int cmd, p, q;
            scanf("%d", &cmd);
            if (cmd == 0) {
                long long v;
                scanf("%d%d%lld",&p,&q,&v);
                range_update(n,p,q,v);
            }
            else {
                scanf("%d%d",&p,&q);  
                cout << range_query(p, q) << endl;
            }
        }
    }

    return 0;
}