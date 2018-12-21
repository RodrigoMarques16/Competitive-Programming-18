#include <iostream>
#include <array>
#include <unordered_map>
#include <set>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 30

using namespace std;

// UVA 10336 - Rank the Languages
//
// flood fill
//
//


int h, w;
array<array<bool, N>, N> visited;
array<array<char, N>, N> map;
unordered_map<char, int> count;

void dfs_impl(int i, int j) {
    if (visited[i][j])
        return;

    visited[i][j] = true;

    char language = map[i][j];

    if (map[i-1][j] == language)
        dfs_impl(i-1, j);

    if (map[i+1][j] == language)
        dfs_impl(i+1, j);

    if (map[i][j-1] == language)
        dfs_impl(i, j-1);

    if (map[i][j+1] == language)
        dfs_impl(i, j+1);
}

void dfs() {
    for(int i = 0; i < h; i++) 
        for(int j = 0; j < w; j++) 
            visited[i][j] = false;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if (!visited[i][j]) {
                dfs_impl(i, j);
                count[map[i][j]]++;
            }
        }
    }
}

struct Cmp {
    using State = pair<char, int>;
    bool operator()(const State& a, const State& b) const { 
        return a.second != b.second ? a.second > b.second : a.first < b.first;
    }
};

int main() {
    ios::sync_with_stdio(0);    
    cin.tie(NULL);

    int n;
    cin >> n;
    
    for(int test = 1; test <= n; test++) {
        cout << "World #" << test << endl;
        cin >> h >> w;

        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                cin >> map[i][j];
            }
        }

        count.clear();

        dfs();
        
        set<pair<char,int>, Cmp> count_set(count.begin(), count.end());

        for(auto pair : count_set) {
            cout << pair.first << ": " << pair.second << endl;
        }
    } 

    return 0;
}