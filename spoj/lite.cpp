#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define log2(n) log(double(n))/log(2.0)
#define N 400001

using namespace std;

int  st[N]    = {0};
bool lazy[N] = {false};

int merge(int a, int b) {
    return a + b;
}

void build(int node, int start, int end) {
}

void refresh(int node, int start, int end) {
    if (lazy[node]) {
        st[node] = end - start + 1 - st[node]; // flip all the bits in [start,end]

        int left  = node * 2;
        int right = node * 2 + 1;
        
        lazy[node]  = false;
        lazy[left]  = !lazy[left];
        lazy[right] = !lazy[right];
    }
}

int query(int node, int start, int end, int x, int y){
    if (start > end || start > y || end < x)
        return 0;

    refresh(node, start, end);

    if (start >= x && end <= y)
        return st[node];

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid = start + (end - start) / 2;

    int a = query(left,  start, mid, x, y);
    int b = query(right, mid+1, end, x, y);

    return merge(a, b);
}

void update(int node, int start, int end, int x, int y) {
    if (start > end || start > y || end < x) { 
        refresh(node, start, end);
        return;
    }
    
    if (start >= x && end <= y) {
        lazy[node] = !lazy[node];
        refresh(node, start, end);
        return;
    }

    refresh(node, start, end);

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid   = start + (end - start) / 2;

    update(left,  start, mid, x, y);
    update(right, mid+1, end, x, y);

    st[node] = merge(st[left], st[right]);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    //init(n-1);
    //build(1, 0, n-1);

    while(m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 0) {
            update(1, 0, n-1, x-1, y-1);
        } else {
            cout << query(1, 0, n-1, x-1, y-1) << endl;
        }
    }

    return 0;
}