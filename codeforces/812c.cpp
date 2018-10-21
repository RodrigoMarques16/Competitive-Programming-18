#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define N 100010

int souvenirs[N];
long long v[N];
int n, budget;

long long calc(int k) {

    for(int i = 0; i < n; i++)
        v[i] = souvenirs[i] + (i + 1) * (long long) k;

    sort(v, v + n);

    long long cost = 0;
    for(int i = 0; i < k; i++)
        cost += v[i];

    return cost;
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> n >> budget;

    for(int i = 0; i < n; i++) {
        cin >> souvenirs[i];
    }

    int low = 0, high = n + 1;

    while(low < high-1) {
        int mid = low + (high - low) / 2;

        if (calc(mid) <= budget)
            low = mid;
        else
            high = mid;
    }

    cout << low << ' ' << calc(low) << '\n';

    return 0;
}