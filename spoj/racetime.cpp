#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 100000

using namespace std;

// SPOJ - RACETIME
//
//

int n;
int bucket_size;
int v[N];
int bucket[N];
int max_in_bucket[N];
int start_index[N];
int end_index[N];

int count(int i, int j, int val) {
    int k = 0;
    for (; i <= j; i++)
        if (v[i] <= val)
            k++;
    return k;
}

int query(int x, int y, int val) {

    if (val == 0)  return 0;
    if (x == y)
        if (val <= v[x]) return 1;
        else return 0;

    int k = 0;
    int a = bucket[x];
    int b = bucket[y];

    // only one bucket
    if (a == b) { 
        return count(x, y, val);
    }
    // first bucket
    for (int i = x; i <= end_index[a] && i <= y; i++) {
        if (v[i] <= val)
            k++;
    }

    // last bucket
    for (int i = start_index[b]; i <= end_index[b] && i <= y; i++) {
        if (v[i] <= val)
            k++;
    }

    // everything in between
    for(int i = a+1; i < b; i++) {
        if (max_in_bucket[i] <= val) {
            k += bucket_size;
        }
        else k += count(start_index[i], end_index[i], val);
    }

    return k;
}

int update(int i, int val) {
    v[i] = val;
    int b = bucket[i];
    max_in_bucket[b] = -1;
    for(int i = start_index[b]; i <= end_index[b]; i++)
        max_in_bucket[b] = std::max(max_in_bucket[b], v[i]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q; 

    bucket_size = sqrt(n);

    int b = 0;
    start_index[1] = 0;

    for(int i = 0; i < n; i++) {
        if (i % bucket_size == 0) {
            end_index[b] = i-1;
            b++;
            start_index[b] = i;
        }
        cin >> v[i];
        bucket[i] = b;
        max_in_bucket[b] = std::max(max_in_bucket[b], v[i]);
    }
    end_index[b] = n-1;

    while(q--) {
        char c;
        cin >> c;
        if (c == 'M') {
            int i, val;
            cin >> i >> val;
            update(i-1, val);
        } else {
            int x, y, val;
            cin >> x >> y >> val;
            x--; y--;
            cout << query(x,y,val) << endl;
        }
    }

    return 0;
}