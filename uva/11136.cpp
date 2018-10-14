#include <iostream>
#include <set>

#define DEBUG(x) cout << #x << ": " << x << endl;

using namespace std;

// 1136 - Hoax or what
//
// Keep track of the bills using a multiset so
// the lowest and highest are always at the begin
// and end respectively
//
// Time: O(n * log(n))
// Size: O(n)

int main() {

    int days, sales, bill;
    long cost;
    multiset<int> bills;

    while(cin >> days, days) {

        bills.clear();
        cost = 0;

        while(days--) {
            cin >> sales;

            while(sales-- > 0) {
                cin >> bill;
                bills.insert(bill);
            }
         
            auto low = bills.begin();
            auto high = --bills.end();

            cost += *high - *low;

            bills.erase(low);
            bills.erase(high);
        }
        
       cout << cost << endl;
    }

    return 0;
}
