#include <iostream>
#include <unordered_map>

using namespace std;

// 11572 - Unique Snowflakes
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2619
//
// Given a sequence of random integers (representing a snowflake),
// find the longest sequence of consecutive unique integers
//
//
//
// Time:  O(n)
// Space: O(n)

int main() {

  ios::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;

  while(t--) {

    unordered_map<int,int> last_seen;
    int n, count, start, max_segment;

    cin >> n;

    count = start = max_segment = 0;
    //last_seen.clear();

    for(int i = 1; i <= n; i++) {

      int sf;
      cin >> sf;

      int index = last_seen[sf];
      
      // Check if the duplicate was found inside the current segment and update count

      if (index != 0) {
        start = max(start, index);
	      count = i - start;
      } else {
        count++;
      }

      last_seen[sf] = i;
      max_segment = max(max_segment, count);
      
    }

    cout << max_segment << endl;
    
  }
  
  return 0;
}
