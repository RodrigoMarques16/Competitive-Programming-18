#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// 11286 - Conformity
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2261
//
// Find the most popular combinations of courses chosen by students and count
// how many students have picked them
// A combination is a set of 5 courses, e.g., (100, 101, 102, 103, 104)
// A combination's popularity is defined by how many students have picked it
//
//  Time:  O(n log n) 
//  Space: O(n)

int main() {
 
    int n;             // Number of students
    int max_pop;       // Number of studens who have the most popular combination
    map<int, int> m;   // Map combinations to their popularity

    cin >> n;

    while(n) {

        m.clear();
        max_pop = 0;
        
        // For every student we read the courses they've signed up for
        // and store them on a vector. We then sort the vector and
        // hash it as a key for the map. Sorting is necessary to make sure 
        // the same combination doesn't get a different hash key.
        // Then we only have to increment the popularity.
        // Boost's hash_combine algorithm is used for hashing.

        while(n--) {

            vector<int> v(5);
            size_t key = 0;

            for(auto &course_id : v) 
                cin >> course_id;

            sort(v.begin(), v.end());

            for(auto it : v)
                key ^= hash<int>()(it) + 0x9e3779b9 + (key << 6) + (key >> 2);

            // Increment and verify if it's the new maximum
            max_pop = max(max_pop, ++m[key]);

        }

        // Since there can be ties we have to iterate through the map
        // once more to find all combinations with max_pop

        int count = 0;
        for(auto it : m)
            if (it.second == max_pop)
                count++;
  
        // count * max_pop is the total number of students
        cout << count * max_pop << endl;

        cin >> n;

    }

    return 0;
}
