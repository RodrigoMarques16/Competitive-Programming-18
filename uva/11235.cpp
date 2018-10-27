#include <iostream>
#include <vector>

#define DEBUG(x) cout << #x << ": " << x << endl;

#define N 100000

using namespace std;

// 11235 - Frequent values
// https://uva.onlinejudge.org/external/112/11235.pdf

// Given a sequence of integers and a sequence of queries consisting of two indexes i and j
// For each query determine the most frequent value between indexes i an dj
//
// Save the frequencies on a segment tree and query it
// Edge cases must be removed from the search range when it includes partial sequences
// as the algorithm will consider the full sequences even if they are outside the range
//
// Time: O(N) building, O(logN) search
// Space: O(5N)

int n;
int st[N] = {0};
int v[N] = {0};
int freq[N] = {0};

int merge(int a, int b) {
    return std::max(a,b);
}

void build(int node, int start, int end) {
    if (start == end) {
        st[node] = freq[start];
        return;
    }

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid = start + (end - start) / 2;

    build(left,  start, mid);
    build(right, mid+1, end);

    st[node] = merge(st[left], st[right]);
}

int query(int node, int start, int end, int x, int y){
    if (start > y || end < x)
        return -1;

    if (start >= x && end <= y)
        return st[node];

    int left  = node * 2;
    int right = node * 2 + 1;
    int mid = start + (end - start) / 2;

    int a = query(left,  start, mid, x, y);
    int b = query(right, mid+1, end, x, y);

    if (a == -1) return b;
    if (b == -1) return a;

    return merge(a, b);
}

int main() {
    //ios::sync_with_stdio(0);
    //cin.tie(NULL);

    cin >> n;

    while(n != 0) {
        
        int q;
        cin >> q;

        vector<int> start(n+5), end(n+5);
        int current, previous, count = 1;
         
        cin >> current;
        previous = current;
        v[0] = current;
        start[0] = 0;

        for(int i = 1; i < n; i++) {
            cin >> current;
            v[i] = current;
            if (current == previous) {
                start[i] = start[i-1];  
            } else {
                for(int j = start[i-1]; j <= i-1; j++){
                    freq[j] = count;
                    end[j]  = i - 1;
                }
                start[i] = i;
                count = 0;
            }
            count++;
            previous = current;        
        }

        for(int j = start[n-1]; j <= n-1; j++) {
            freq[j] = count;
            end[j]  = n - 1;
        }

        build(1, 0, n-1);

        while(q--) {
            int x, y;
            cin >> x >> y;
            
            x--; 
            y--;

            if(v[x] == v[y]) {  
                // all elements are the same
				cout << y - x + 1 << endl;
			}
            else {
                int segment1 = end[x] - x + 1;   // frequency of leftmost element
				int segment2 = y - start[y] + 1; // frequency of rightmost element

                int ans = std::max(segment1, segment2);

                if(start[y] - end[x] > 1) {
                    // middle segment is worth considering
					int segment3 = query(1, 0, n-1, end[x]+1, start[y]-1);
                    cout << std::max(segment3, ans) << endl;
				}else{
                    // only two different elements
                    cout << ans << endl;
				}
            }
        }
        cin >> n;
    }

    return 0;
}