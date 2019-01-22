#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 100000
#define M 1000000005

using namespace std;

int n;
int bucket_size;
int v[N];
int seg[N];
int bucket[N];
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
    int k = 0;
    int a = bucket[x];
    int b = bucket[y];

    if (a == b)
        return count(x, y, val);

    for (int i = x; i <= end_index[a] && i <= y; i++)
       if (v[i] <= val)
           k++;

    for (int i = start_index[b]; i <= end_index[b] && i <= y; i++)
        if (v[i] <= val)
            k++;

    for(int i = a+1; i < b; i++) {
        int* pos = std::upper_bound(seg+start_index[i], seg+end_index[i]+1, val);

        if (pos != seg+end_index[i]+1)
            k += std::distance(seg+start_index[i], pos);
        else k += bucket_size;
    }

    return k;
}

void update(int i, int val) {
    int b = bucket[i];
    int* pos = std::lower_bound(seg+start_index[b], seg+end_index[b]+1, v[i]);
    v[i] = *pos = val;
    std::sort(seg+start_index[b], seg+end_index[b]+1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int q;
    cin >> n >> q;
    bucket_size = sqrt(n);

    int b = 0;
    start_index[0] = 0;

    for(int i = 0; i < n; i++) {
        if (i > 0 && i % bucket_size == 0) {
            end_index[b] = i-1;
            b++;
            start_index[b] = i;
        }
        cin >> v[i];
        seg[i] = v[i];
        bucket[i] = b;
    }
    end_index[b] = n-1;

    for(int i=0; i < n;) {
        int j = std::min(i+bucket_size, n);
        std::sort(seg+i, seg+j);
        i = j;
    }

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
            cout << query(x-1,y-1,val) << endl;
        }
    }

    return 0;
}