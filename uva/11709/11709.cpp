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

    void clear() {
        adj.clear();
    }

    void add(const T& node) {
        adj.emplace(std::make_pair(node, vector<T>{}));
    }

    void addEdge(const T& node, const T& next) {
        adj[node].emplace_back(next);
    }

    vector<T>& getEdges(const T& node) {
        return adj[node];
    }

    void print() const {
        for (auto& it : adj)
            printEdges(it.first);
    }

    void printEdges(const T& node) const {
        cout << node << ": ";
        for(auto& next : getEdges(node))
            cout << next << " ";
        cout << endl;
    }

    void dfs(const T& node) const {
        stack<T> st{};
        mark_map visited{};

        // Mark all nodes as not visited
        for(auto& it : adj)
            // unordered_map iterators are of the form
            // it.first = key, it.second = value
            visited[it.first] = false;

        //cout << source << " ";

        for(auto& next : getEdges(node))
            if (!visited[next])
                dfs_impl(next, visited);
    }

    void dfs_impl(const T& node, mark_map& visited) {
        // Mark this node as visited
        visited[node] = true;
        //cout << node << " ";

        // Search through all nodes accessible from here
        for(auto& next : getEdges(node))
            if (!visited[next])
                dfs_impl(next, visited);
    }

    stack<T> fillOrder() {
        stack<T> st{};
        mark_map visited{};

        for(auto& it : adj)
            visited[it.first] = false;

        for(auto& it : adj)
            if (!visited[it.first])
                fillOrder_impl(it.first, visited, st);
    
        return st;
    }

    void fillOrder_impl(const T& node, mark_map& visited, stack<T>& st) {
        // Mark this node as visited
        visited[node] = true;

        // Search through all nodes accessible from here
        for(auto& next : getEdges(node))
            if (!visited[next])
                fillOrder_impl(next, visited, st);

        st.push(node);
    }

    Graph<T> transpose() {
        Graph<T> g{};

        // Iterate through every node in the graph
        for(auto& it : adj)
            // Iterate through every adjacent node
            // it.first  = node
            // it.second = node's adjacency vector
            for(auto& adjacent : it.second)
                g.addEdge(adjacent, it.first);

        return g;
    }

    void kosaraju() {
        stack<T> st = this->fillOrder();
        Graph<T> transpose = this->transpose();

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