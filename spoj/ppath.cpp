#include <iostream>
#include <queue>
#include <unordered_map>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define MAX 10000

using namespace std;

// SPOJ PPATH - Prime Path
// https://www.spoj.com/problems/PPATH/
//
// Direct BFS application. For each prime generate all primes obtainable
// from it by switching a single digit.
//
// The implementation details of the problem are checking if a number 
// you've generated is a prime (use sieve of Eratosthenes) and checking
// if the number is withing the problem's bounds (4 digits)

// compile time square root
// https://github.com/wichtounet/articles/blob/master/src/sqrt/smart_constexpr.cpp
static constexpr std::size_t ct_sqrt(std::size_t res, std::size_t l, std::size_t r){
    if(l == r){
        return r;
    } else {
        const auto mid = (r + l) / 2;

        if(mid * mid >= res){
            return ct_sqrt(res, l, mid);
        } else {
            return ct_sqrt(res, mid + 1, r);
        }
    }
}

static constexpr std::size_t ct_sqrt(std::size_t res){
    return ct_sqrt(res, 1, res);
}

// compile time primes
// https://gist.github.com/rongjiecomputer/d52f34d27a21b8c9c9e82ca85b806640
template <size_t N>
struct Sieve {
    public:
    bool is_prime[N];

    constexpr Sieve() : is_prime{} {
        is_prime[0] = is_prime[1] = false;
        
        for (size_t i = 2; i < N; i++) 
            is_prime[i] = true;

        for (size_t i = 2; i < ct_sqrt(N); i++)
            if (is_prime[i])
                for (size_t j = i*i; j < N; j += i) 
                    is_prime[j] = false;
    }
};

constexpr auto sieve = Sieve<MAX>();

int bfs(string start, string goal) {
    queue<string> q;
    unordered_map<string, bool> visited;
    unordered_map<string, int> depth;
   
    q.push(start);
    visited[start] = true;
    depth[start] = 0;

    while(!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == goal) {
            return depth[current];
        }

        for(int i = 0; i < 4; i++) {
    	    for(int j = 0; j < 10; j++) {
                string next{current};
                next[i] = j + '0';

                int num = stoi(next);
                if (num >= 1000 && !visited[next] && sieve.is_prime[num]) {
                    q.push(next);
                    visited[next] = true;
                    depth[next] = depth[current] + 1;
                }
            }
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n;
    cin >> n;

    while(n--) {
        string a, b;
        cin >> a >> b;
        cout << bfs(a, b) << endl;
    }

    return 0;
}