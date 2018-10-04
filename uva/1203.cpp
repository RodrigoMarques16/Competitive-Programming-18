#include <iostream>
#include <queue>
#include <map>

#define DEBUG(x) cout << #x << ": " << x << endl;

using namespace std;

typedef pair<int,int> query;
typedef vector<query> data;

auto cmp = [](const query& e1, const query& e2) { 
    if (e1.first == e2.first)
        return e1.second > e2.second;
    return e1.first > e2.first;
};

int main() {

    string command;
    priority_queue<query, data, decltype(cmp)> pq(cmp);
    int periods[3005];

    while(cin >> command, command != "#") {
        int id, period;
        cin >> id >> period;
        pq.push(make_pair(period, id));
        periods[id] = period;
    }

    int k, tick = 0;
    cin >> k;

    while(k--) {
        query q = pq.top();
        tick = q.first;

        cout << q.second << endl;
        
        int next_tick = tick + periods[q.second];
        
        pq.pop();
        pq.push(make_pair(next_tick, q.second));
        
    }


    return 0;
}