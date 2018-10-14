#include <iostream>
#include <unordered_map>

using namespace std;

// 11572 - Unique Snowflakes
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2619
//
// Given a sequence of random integers (representing a snowflake),
// find the longest segment of consecutive unique integers
//
// Save the last position a number was seen at using an unordered map
//
// Keep track of the current segment using variables start (where it begins) 
// and count (its size)
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

    for(int i = 1; i <= n; i++) {

      int sf;
      cin >> sf;

      int index = last_seen[sf];

      if (index != 0) {
        // If the number was last seen inside the current segment then update start and 
        // count to match the new segment
        // If the number was last seen before the current segment then count doesn't change
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
