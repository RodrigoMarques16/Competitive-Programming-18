#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define log2(n) log(double(n))/log(2.0)
#define N 100000

using namespace std;

// KQUERY
// 
//

typedef struct _Query {
    int i;
    int j;
    int k;
    int index;
} Query;

bool sortK(const _Query &a, const _Query &b) {
    return a.k > b.k;
}

bool sortIndex(const _Query &a, const _Query &b) {
    return a.index < b.index;
}

int v[N];
int ans[N];
vector<int> st;


void initTree(int size){
	int count = 2*pow(2,floor(log2(size)) + 1);
	st.resize(count);
}

int merge(int a, int b) {
    return a + b;
}

void build(int node, int start, int end) {
    if (start == end) {
        st[node] = 1;
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
        return 0;

    if (start >= x && end <= y)
        return st[node];

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid = start + (end - start) / 2;

    int a = query(left,  start, mid, x, y);
    int b = query(right, mid+1, end, x, y); 

    return merge(a, b);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> v[i];

    std::sort(v, v+n, std::greater<int>());

    initTree(n-1);
    build(1, 0, n-1);

    for(int i = 1; i < st.size(); i++) {
        DEBUG(st[i]);
    }

    int q;
    cin >> q;
    vector<Query> queries;
    vector<int> ans(q);

    for(int index = 0; index < q; index++) {
        int i, j, k;
        cin >> i >> j >> k;
        queries.push_back({--i, --j, k, index});
    }

    std::sort(queries.begin(), queries.end(), sortK);

    return 0;
}