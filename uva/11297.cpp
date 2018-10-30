#include <iostream>
#include <vector>
#include <cmath>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define log2(n) log(double(n))/log(2.0)

using namespace std;

vector<_Node> st;

void initTree(vector<int> &st, int size){
	int count = 2*pow(2,floor(log2(size)) + 1);
	st.resize(count);
}

typedef struct _Node {
    vector<_Node> st;
    int max_pop;
    int min_pop;
} Node;

int merge(int a, int b) {
}

void build(vector<int> &st, int node, int start, int end) {
    if (start == end) {
        
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

    int n;
    cin >> n;
    
    int c[n+5][n+5];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }

    initTree(st, n-1);
    build(st, 1, 0, n-1);


    int q;
    cin >> q;  
    while(q--) {
        char c;
        if (c == 'q'){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
        } else {
            int x, y, v;
            cin >> x >> y >> v;


        }
    }

    return 0;

}