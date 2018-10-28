#include <iostream>
#include <vector>
#include <cmath>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define log2(n) log(double(n))/log(2.0)
#define N 100000

using namespace std;

// 12532 - Interval Product
// https://uva.onlinejudge.org/external/125/12532.pdf
//
// Build a segment tree that saves each number's signal
//
// Time: building: O(N); searching: O(log N)
// Space: O(2N)


const char signal[3] = {'-','0','+'};

int v[N];
vector<int> st;

void initTree(int size){
	int count = 2*pow(2,floor(log2(size)) + 1);
	st.resize(count);
}

int signum(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
int merge(int a, int b) {
    return a * b;
}

void build(int node, int start, int end) {
    if (start == end) {
        st[node] = signum(v[start]);
        return;
    }

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid   = start + (end - start) / 2;

    build(left,  start, mid);
    build(right, mid+1, end);

    st[node] = merge(st[left], st[right]);
}

int query(int node, int start, int end, int x, int y){
    if (start > y || end < x)
        return 1;

    if (start >= x && end <= y)
        return st[node];

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid = start + (end - start) / 2;

    int a = query(left,  start, mid, x, y);
    int b = query(right, mid+1, end, x, y);

    return merge(a, b);
}

void update(int node, int start, int end, int x, int val) {

    if (start > x || end < x) 
        return;

    if (start == end && start == x) {
        st[node] = signum(val);
        return;
    }

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid   = start + (end - start) / 2;

    update(left,  start, mid, x, val);
    update(right, mid+1, end, x, val);

    st[node] = merge(st[left], st[right]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n, k;

    while(cin >> n >> k) {
        for(int i = 0; i < n; i++)
            cin >> v[i];

        initTree(n-1);
        build(1,0, n-1);

        int a, b;
        char c;
        while(k--) {
            cin >> c >> a >> b;
            a--;
            if (c == 'C') {
                v[a] = b;
                update(1, 0, n-1, a, b);
            } else {
                b--;
                cout << signal[query(1, 0, n-1, a, b)+1]; 
            }
        }
        cout << endl;
    }

    return 0;
}