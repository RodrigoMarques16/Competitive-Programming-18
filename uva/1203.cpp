#include <iostream>
#include <queue>
#include <map>

using namespace std;

// 1203 - Argus
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3644
//
// Given a list of repeating queries with different time intervals and a number K,
// print the first K queries to run.
// 
// We can use a priority queue with a custom comparator to keep track of the running queries.
// The next query will always be at the top of the queue.
// 
// After removing a query from the queue we update its next tick before putting it
// back in.
//
// Time:  O(n log n) 
// Space: O(n)


typedef struct {
    int id;
    int period;
    int next_tick;
} query;

typedef vector<query> datastream;

auto cmp = [](const query& e1, const query& e2) { 
    if (e1.next_tick == e2.next_tick)
        return e1.id > e2.id;
    return e1.next_tick > e2.next_tick;
};

int main() {

    string command;
    priority_queue<query, datastream, decltype(cmp)> pq(cmp);

    ios::sync_with_stdio(0);
    cin.tie(0);

    while(cin >> command, command != "#") {
        int id, period;
        cin >> id >> period;
        pq.push({id, period, period});
    }

    int k, tick = 0;
    cin >> k;

    while(k--) {
        query q = pq.top();
        cout << q.id << endl;
        pq.pop();
        pq.push({q.id, q.period, q.period + q.next_tick});
    }

    return 0;
}