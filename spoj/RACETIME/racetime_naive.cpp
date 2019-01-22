#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 100000
#define M 1000000005

using namespace std;

// SPOJ - RACETIME

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

void update(int i, int val) {    
    v[i] = val;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q; 

    for(int i = 0; i < n; i++)
        cin >> v[i];

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
            cout << count(x-1,y-1,val) << endl;
        }
    }

    return 0;
}