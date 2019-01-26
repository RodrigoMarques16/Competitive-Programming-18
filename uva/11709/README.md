# UVA 11709 -  Trust Groups

[Trust Groups](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2756)

You're given the trust relationship between employees.  

Your task is to find the minimum number of groups of employees who trust each other (stable groups). In other words: each employee belongs the largest possible group where they trust everyone.

- Trust is unidirectional.  
  If employee A trusts employee B it doesn't mean employee B has to trust employee A.

- Trust is transitive.  
  If employee A trusts employee B, and employee B trusts employee C, then A trusts C.


## Input

Starts with two integers, _P_, the number of employees, and _T_, the number of trust relationships.

Followed by P lines, each containing the name of an employee
in the form:

_Surname_, _Name_

Finally, T pairs of lines. The first line contains the name of an employee and the second line the name of an employee the former trusts (trust isn't bidirectional).

Test cases in this format repeat until the input `0 0`

## Output

The number of groups for each test case.

### Example

<pre>
<b>Input:</b>
3 2
McBride, John
Smith, Peter
Brown, Anna
Brown, Anna
Smith, Peter
Smith, Peter
Brown, Anna
3 2
McBride, John
Smith, Peter
Brown, Anna
Brown, Anna
Smith, Peter
McBride, John
Smith, Peter
0 0

<b>Output:</b>
2
3
</pre>

---

## Solution

The description of this problem matches that of [strongly connected components](https://en.wikipedia.org/wiki/Strongly_connected_component). A stable group of employees is the same as a maximal (can't add more nodes) strongly connected component.  

To find all strongly connected components in a graph we can use [Kosaraju's algorithm](https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm).

This solution is based on the implementation at <https://www.geeksforgeeks.org/strongly-connected-components/>.

## Data structures

### Graph class

[unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map) is slow. Alternatively, for speed, we could use it only to map employee names to id's, and use a `vector<int>` instead. But this is simpler.

```cpp
template<typename T>
class Graph {
    // Map nodes to a vector of their adjacent nodes
    using adjacency_list = unordered_map<T, vector<T>>;

    // Map nodes to a boolean. (eg: keep track of visited nodes in dfs)
    using mark_map = unordered_map<T, bool>;

    adjacency_list adj;

public:

    // Add a single node to the graph
    // Constructs the node in-place and default initializes
    // the node's adjacency vector
    void add(const T& node) {
        adj.emplace(std::make_pair(node, vector<T>{}));
    }

    // Add an edge to the graph
    void addEdge(const T& node, const T& next) {
        adj[node].push_back(next);
    }

    // Returns a reference to a node's adjacency vector
    vector<T>& getEdges(const T& node) {
        return adj[node];
    }
}
```

Those are the essentials for the graph structure.

## Kosaraju's Algorithm

Kosaraju's algorithm follows 3 steps:

1. Traverse the graph with DFS and use a stack to keep track of when you finish processing each node.

2. Get the transpose of the graph by inverting the edges.

3. Traverse the transpose with DFS using the stack's ordering.

Each iteration of step 3 is guaranteed to find a maximal strongly connected component.

### 1. Ordering

Each node is pushed to the stack after all nodes accessible
from it have been processed.

```cpp
stack<T> fillOrder() {
    stack<T> st{};
    mark_map visited{};

    // Initialize all nodes as not visited
    for(auto& it : adj)
        visited[it.first] = false;

    // Iterate trhough every node not visited yet
    for(auto& it : adj)
        if (!visited[it.first])
           fillOrder_impl(it.first, visited, st);

    return st;
}

void fillOrder_impl(const T& node, mark_map& visited, stack<T>& st) {
    // Mark this node as visited
    visited[node] = true;

    // Visit all nodes accessible from this one
    for(auto& next : getEdges(node))
        if (!visited[next])
            fillOrder_impl(next, visited, st);

    // Push this node to the stack
    st.push(node);
}
```

### Transpose

Simply flip all the edges in the graph.

```cpp
Graph<T> transpose() {
    Graph<T> g{};

    // Iterate through every node in the graph
    for(auto& it : adj)
        // Iterate through every adjacent node
        // it.first  = node
        // it.second = node's adjacency vector
        for(auto& adjacent : it.second)
            // Add the reverse to the new graph
            g.addEdge(adjacent, it.first);

    return g;
}
```

### DFS

Depth first traversal. Each iteration over the transpose will mark all nodes of a SCC as visited.

```cpp
void dfs_impl(const T& node, mark_map& visited) {
    // Mark this node as visited
    visited[node] = true;

    // Iterate through every adjacent node
    for(auto& next : getEdges(node))
        if (!visited[next])
           dfs_impl(next, visited);
}
```

### Kosaraju

```cpp
void kosaraju() {
    stack<T> st = this->fillOrder();
    Graph<T> transpose = this->transpose();

    // Mark all nodes as not visited
    mark_map visited{};
    for(auto& it : adj)
        visited[it.first] = false;

    // Initialize SCC counter
    int count = 0;

    // Start a DFS on every yet unvisited node
    // Each traversal will go through all the members
    // of a single SCC so repeats aren't counted
    while(!st.empty()) {
        T node = st.top();
        st.pop();

        if (!visited[node]) {
            transpose.dfs_impl(node, visited);
            count++;
        }
    }

    // Print the number of SCC's found
    cout << count << endl;
}
```

## Full code

```cpp
#include <iostream>
#include <vector>
#include <vector>
#include <stack>
#include <unordered_map>
#include <functional>

#define DEBUG(x) cout << #x << ": " << x << endl;
#define N 1000

using namespace std;

template<typename T>
class Graph {
    using adjacency_list = unordered_map<T, vector<T>>;
    using mark_map = unordered_map<T, bool>;

    adjacency_list adj;

public:

    Graph() = default;
    ~Graph() = default;

    void add(const T& node) {
        adj[node];
    }

    void addEdge(const T& node, const T& next) {
        adj[node].push_back(next);
    }

    vector<T> getEdges(const T& node) const {
        return adj.at(node);
    }

    void dfs_impl(const T& node, mark_map& visited) {
        visited[node] = true;

        for(auto& next : getEdges(node))
            if (!visited[next])
                dfs_impl(next, visited);
    }

    void fillOrder(stack<T>& st) {
        mark_map visited{};

        for(auto& it : adj)
            visited[it.first] = false;

        for(auto& it : adj)
            if (!visited[it.first])
                fillOrder_impl(it.first, visited, st);
    }

    void fillOrder_impl(const T& node, mark_map& visited, stack<T>& st) {
        visited[node] = true;

        for(auto& next : getEdges(node))
            if (!visited[next])
                fillOrder_impl(next, visited, st);

        st.push(node);
    }

    Graph<T> transpose() {
        Graph<T> g{};

        for(auto& it : adj)
            for(auto& adjacent : it.second)
                g.addEdge(adjacent, it.first);

        return g;
    }

    void kosaraju() {
        stack<T> st{};
        this->fillOrder(st);
        Graph<string> transpose = this->transpose();

        mark_map visited{};
        for(auto& it : adj)
            visited[it.first] = false;

        int count = 0;
        while(!st.empty()) {
            T node = st.top();
            st.pop();

            if (!visited[node]) {
                transpose.dfs_impl(node, visited);
                count++;
            }
        }

        cout << count << endl;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int p, t;
    while(cin >> p >> t) {

        if (p == 0 && t == 0)
            break;

        Graph<string> g;

        cin.ignore();
        while(p--) {
            string name;
            getline(cin, name);
            g.add(name);
        }

        while(t--) {
            string person, trusted;
            getline(cin, person);
            getline(cin, trusted);
            g.addEdge(person, trusted);
        }

        g.kosaraju();
    }

    return 0;
}
```