#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

#define DEBUG(x) cout << #x << ": " << x << endl;

#define N 10005

using namespace std;

// UVA 10534 - Wavio Sequence
// Combined longest increasing and decreasing sequences
//
// Calculate the lis and lds for each position, then
// iterate over them to find the longest sequence.
// If at a position 'i', lis[i] != lds[i] then use the
// smallest of them.

int lis[N]; 
int lds[N]; 

void solve_lis(int arr[], int n) { 
    int size = 1;
    vector<int> v; 
    v.push_back(arr[0]);
    lis[0] = 1;    
    for (int i = 1; i < n; i++) { 
        // arr[i] extends the lis
        if (arr[i] > v.back()) {
            v.push_back(arr[i]);
            lis[i] = ++size;
        }
        else {
            // lower_bound returns an iterator
            // to the first element that is not less
            // than 'arr[i]', which is also the last
            // element of the lis ending at 'i'
            int temp = std::lower_bound(v.begin(), v.end(), arr[i])
                     - v.begin();
            
            // update the sequence
            v[temp] = arr[i];

            //for(int i = 0; i < v.size(); i++)
                //cout << v[i] << " ";
            //cout << endl;
            
            lis[i] = temp+1;
        }
        //for(int i = 0; i < v.size(); i++)
            //cout << v[i] << ", ";
        //cout << endl;
    } 
} 

void solve_lds(int arr[], int n) { 
    int size = 1;
    vector<int> v; 
    v.push_back(arr[n-1]);
    lds[n-1] = 1;    
    for (int i = n-2; i >= 0; i--) { 
        if (arr[i] > v.back()) {
            v.push_back(arr[i]);
            lds[i] = ++size;
        }
        else {
            int temp = std::lower_bound(v.begin(), v.end(), arr[i])
                    - v.begin();
            v[temp] = arr[i];
            lds[i] = temp+1;
        }
    } 
} 

int solve(int n) {
    int max = -1;
    for(int i = 0; i < n; i++) {
        int min = std::min(lis[i], lds[i]);
        if (max < min)
            max = min;
    }
    return max*2-1;
}

int main() {
    int n;
    ios::sync_with_stdio(0);
    cin.tie(NULL);
   
    //while(scanf("%d", &n) == 1) {
    while(cin >> n) {
        int v[n];
        for(int i = 0; i < n; i++) {
            //scanf("%d", &v[i]);
            cin >> v[i];
        }

        if (n==1) {
            printf("1\n");
            continue;
        }

        solve_lis(v, n);
        solve_lds(v, n);
        
        /*
        for(int i = 0; i < n; i++)
            cout << lis[i] << " ";
        cout << endl;
        for(int i = 0; i < n; i++)
            cout << lds[i] << " ";
        cout << endl;*/
        cout << solve(n) << '\n';
        //printf("%d\n", solve(n));
    }

    return 0;
}