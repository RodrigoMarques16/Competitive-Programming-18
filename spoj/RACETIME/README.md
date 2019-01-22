# SPOJ - Race Against Time

[RACETIME](https://www.spoj.com/problems/RACETIME/)

You have an array of numbers _A_ with size _N_.
You have to answer _Q_ queries of the following operations:

- Change a number at position _i_ to _X_, prefixed by _M_
- Count how many numbers inside a given range \[_P_,_Q_\], are lower than a given value _X_, prefixed by _C_

## Input

The first line gives the integers _N_ and _Q_, and the next N lines give the initial values of _A<sub>i</sub>_. Finally, the next _Q_ lines each contain a query of the form `M i X` or `C P Q X`.

## Output

Print the answer to each 'C' query, one per line.

### Example

<pre>
<b>Input:</b>
4 6
3
4
1
7
C 2 4 4
M 4 1
C 2 4 4
C 1 4 5
M 2 10
C 1 3 9

<b>Output:</b>
2
3
4
2
</pre>

---

## Solution 1 (Naive)

Work with the given array naively.

```cpp
// Count all values lower than val
// in the interval [i,j]
int count(int i, int j, int val) {
    int k = 0;
    for (; i <= j; i++)
        if (v[i] <= val)
            k++;
    return k;
}

// Update the value at v[i]
void update(int i, int val) {
    v[i] = val;
}

int main() {
    // input loop
    // call count for C queries
    // call update for M queries
}

```

---

## Solution 2 (Square Root Decomposition)

Start by dividing the array in sorted buckets of size sqrt(_N_).

**Eg:**

>The array:  
> 3 4 1 7 45 34 41 26 10 46 43 39 11 44 18 1
>
>would be partitioned as:  
>1 3 4 7 **|** 26 34 41 45 **|** 10 39 43 45 **|** 1 11 18 44  

To find how many members of a bucket are lower than a value we need only to find the first member equal or larger than that value.

**Eg:**

>With the above array, if we wanted to find all values lower than 40 in the second bucket we stop counting when we reach 41.

The caveat of this method is that it only works if a bucket is completely included. By sorting we're losing the original ordering of the array (which is the ordering the queries are asking about)

**Eg:**

>Taking the first 4 elements  
>3 4 1 7  
>
>And the corresponding bucket  
>1 3 4 7  
>
>Say we ask for all numbers lower than 2 in the range [0,1]. Obviously there's none in the original array but querying the sorted bucket would give '1'.

So, for partially included buckets we still go with the naive 'count them one by one' solution. This happens when the range we're looking at is smaller than a bucket, or the first and/or last bucket are partially included.

Now to implement this:

### Data structures

We will use some auxiliary structures to make the code easier to understand:

```cpp
int n;              // Number of elements in the array
int bucket_size;    // Size of each bucket
int v[N];           // The array
int seg[N];         // Segmented array
int bucket[N];      // bucket[i] saves whhich bucket position i belongs to
int start_index[N]; // start_index[b] saves the position where bucket b begins
int end_index[N];   // Analogous to start_index
```

Check the full code below to see how to initialize them.

### Count

`count` is the same as the naive solution.

### Update

`update` now has to find the element inside its bucket since it's position is lost when sorted.
Then we have to sort it again.

[std::lower_bound](https://en.cppreference.com/w/cpp/algorithm/lower_bound)  
[std::sort](https://en.cppreference.com/w/cpp/algorithm/sort)

```cpp
void update(int i, int val) {
    int b = bucket[i];
    // std::lower_bound checks the range [first, last[, hence the +1
    // this finds the first position v[i] appears in the bucket
    // we know for sure v[i] exists in the bucket so we don't have to check for failure
    int* pos = std::lower_bound(seg+start_index[b], seg+end_index[b]+1, v[i]);
    v[i] = *pos = val;
    std::sort(seg+start_index[b], seg+end_index[b]+1);
}
```

### Query

Now to answer queries we need to consider each case:

- The range is of equal size or smaller than a bucket
- The range begins or ends in the middle of a bucket
- Every bucket between the first and last is guarantted to be fully contained

[std::upper_bound](https://en.cppreference.com/w/cpp/algorithm/upper_bound)  
[std::distance](https://en.cppreference.com/w/cpp/iterator/distance)

```cpp
int query(int x, int y, int val) {
    int k = 0;
    int a = bucket[x];
    int b = bucket[y];

    // If the range is contained inside a single bucket
    if (a == b)
        return count(x, y, val);

    // Iterate the first bucket starting at 'x'
    for (int i = x; i <= end_index[a]; i++)
       if (v[i] <= val)
           k++;

    // Iterate the last bucket
    for (int i = start_index[b]; i <= end_index[b]; i++)
        if (v[i] <= val)
            k++;

    // All the other buckets are guaranteed to be fully within the range
    for(int i = a+1; i < b; i++) {
        // std::upper_bound finds the first element greater than 'val' in the current bucket
        int* pos = std::upper_bound(seg+start_index[i], seg+end_index[i]+1, val);

        // If there's no element lower than 'val' then we add the entire bucket
        // Otherwise, std::distance lets us count positions between with iterators.
        if (pos != seg+end_index[i]+1)
            k += std::distance(seg+start_index[i], pos);
        else k += bucket_size;
    }
    return k;
}
```

### Full code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 100000
#define M 1000000005

using namespace std;

int n;
int bucket_size;
int v[N];
int seg[N];
int bucket[N];
int start_index[N];
int end_index[N];

int count(int i, int j, int val) {
    int k = 0;
    for (; i <= j; i++)
        if (v[i] <= val)
            k++;
    return k;
}

int query(int x, int y, int val) {
    int k = 0;
    int a = bucket[x];
    int b = bucket[y];

    if (a == b)
        return count(x, y, val);

    for (int i = x; i <= end_index[a] && i <= y; i++)
       if (v[i] <= val)
           k++;

    for (int i = start_index[b]; i <= end_index[b] && i <= y; i++)
        if (v[i] <= val)
            k++;

    for(int i = a+1; i < b; i++) {
        int* pos = std::upper_bound(seg+start_index[i], seg+end_index[i]+1, val);

        if (pos != seg+end_index[i]+1)
            k += std::distance(seg+start_index[i], pos);
        else k += bucket_size;
    }

    return k;
}

void update(int i, int val) {
    int b = bucket[i];
    int* pos = std::lower_bound(seg+start_index[b], seg+end_index[b]+1, v[i]);
    v[i] = *pos = val;
    std::sort(seg+start_index[b], seg+end_index[b]+1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int q;
    cin >> n >> q;
    bucket_size = sqrt(n);

    int b = 0;
    start_index[0] = 0;

    for(int i = 0; i < n; i++) {
        if (i > 0 && i % bucket_size == 0) {
            end_index[b] = i-1;
            b++;
            start_index[b] = i;
        }
        cin >> v[i];
        seg[i] = v[i];
        bucket[i] = b;
    }
    end_index[b] = n-1;

    for(int i=0; i < n;) {
        int j = std::min(i+bucket_size, n);
        std::sort(seg+i, seg+j);
        i = j;
    }

    while(q--) {
        char c;
        cin >> c;
        if (c == 'M') {
            int i, val;
            cin >> i >> val;
            update(i-1, val);
        } else {
            int x, y, val;
            cin >> x >> y >> val;
            cout << query(x-1,y-1,val) << endl;
        }
    }

    return 0;
}
```