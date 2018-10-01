#include <iostream>
#include <unordered_map>

using namespace std;

// 11572 - Unique Snowflakes
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2619
//
// Given a sequence of random integers (representing a snowflake),
// find the longest sequence of consecutive unique integers
//
// time:  O(n)
// space: O(n)
//
// For each number, we keep track of the last position it appeared in
// using a map. STL's unordered map is used for speed (~43% faster).
//
// 'sf'    is a snowflake's id
// 'count' is the # of unique numbers in the current segment
// 'start' is the position before where the current segment starts
//         (the real position is start+1)
// 'max_sequence' is the longest sequence of unique integers

// The algorithm increments count while new snowflakes are inserted
// When a duplicate it hits a duplicate, it checks if it was last
// seen inside the current segment, or before.
//
// If it's found before the current, nothing changes, the segment is
// still made up of unique numbers

// If it's found inside, then the segment can't continue and count
// has to be reset
//
// Example: the segment '7 4 0 9' (size 4)
//
// 7 |4| 0 9 |4| 8 8 2 4 5 5 1
//
// The second '4' is inserted, but it already appears once,
// so we discard the segment, and begin a new one at position 3
// The new segment will be '0 9' (size 2)
//
// The number of elements in the new segment can be calculated by
// subtracting its start position from its end position
//     (hence the above 'real position' comment)
//
// For '4': 5-(2+1) = 2
//
// The algorithm increments count at the end of every iteration
// so we don't need to consider the current number

int main() {

  unordered_map<int,int> last_seen;
  int t, n, sf, start, count, max_sequence;

  cin >> t;

  while(t--) {
    cin >> n;

    count = start = max_sequence = 0;
    last_seen.clear();

    for(int i = 1; i <= n; i++) {
      cin >> sf;

      // Get the position the current number was last seen in
      // 0 if not
      int index = last_seen[sf];
      
      if (index != 0) {
	// Check if the duplicate was found inside the
	// current segment and update count
        start = max(start, index);
	count = i-start-1;
      }

      count++;
      last_seen[sf] = i;

      max_sequence = max(max_sequence, count);
      
    }

    cout << max_sequence << endl;
    
  }
  
  return 0;
}
