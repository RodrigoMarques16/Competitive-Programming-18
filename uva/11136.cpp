#include <iostream>
#include <set>

#define DEBUG(x) cout << #x << ": " << x << endl;

using namespace std;

// 1136 - Hoax or what
// For every sale, its bill can be inserted in a
// ballot. Each day, the difference between the
// highest and lowest bills in the ballot are
// awarded to a customer. 
// 
// The ballot is not emptied at the end of the 
// day.
//
// Given n days, calculate the total cost of 
// the promotion.

// This problem is pretty straight forward.
//
// With a multiset, we can insert bills into
// it in every repetition while it stays sorted.
// The lowest bill will be at the beggining, the
// highest bill at end.
//
// Knowing that we can just remove those bills
// from the set and calculate the cost for that day
 
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
