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
    using mark_map = unordered_map<string, bool>;

    adjacency_list adj;

public:
    Graph() {
        /* do nothing */
    }

    ~Graph() {
        /* do nothing */
    }

    void clear() {
        adj.clear();
    }

    void add(const T& node) {
        adj[node];
    }

    void addEdge(const T& node, const T& next) {
        adj[node].push_back(next);
    }

    vector<T> getEdges(const T& node) {
        return adj[node];
    }

    void print() {
        for (auto it : adj)
            printEdges(it.first);
    }

    void printEdges(const T& node) {
        cout << node << ": ";
        for(auto next : getEdges(node))
            cout << next << " ";
        cout << endl;
    }

    void dfs(T source) {
        stack<T> st{};
        mark_map visited{};

        // Mark all nodes as not visited
        for(auto it : adj)
            // unordered_map iterators are of the form
            // it.first = key, it.second = value
            visited[it.first] = false;

        //cout << source << " ";

        for(auto next : getEdges(source))
            if (!visited[next]) {
                dfs_impl(next, visited);
            }
    }

    void dfs_impl(const T& node, mark_map& visited) {
        // Mark this node as visited
        visited[node] = true;
        //cout << node << " ";

        // Search through all nodes accessible from here
        for(auto next : getEdges(node))
            if (!visited[next]) {
                dfs_impl(next, visited);
            }
    }

    void fillOrder(stack<T>& st) {
        mark_map visited{};

        for(auto it : adj)
            visited[it.first] = false;

        for(auto it : adj)
            if (!visited[it.first])
                fillOrder_impl(it.first, visited, st);
    }

    void fillOrder_impl(const T& node, mark_map& visited, stack<T>& st) {
        // Mark this node as visited
        visited[node] = true;

        // Search through all nodes accessible from here
        for(auto next : getEdges(node))
            if (!visited[next]) {
                fillOrder_impl(next, visited, st);
            }

        st.push(node);
    }

    Graph<T> transpose() {
        Graph<T> g{};
        
        for(auto it : adj) {
            //Alias
            const T& node         = it.first;
            const vector<T>& adjList = it.second;
            
            // Add the reverse of all edges to the new graph
            for(auto adjacent : adjList)
                g.addEdge(adjacent, node);
        }

        return g;
    }

    void kosaraju() {
        stack<T> st{};
        this->fillOrder(st);
        Graph<string> transpose = this->transpose();

        mark_map visited{};
        for(auto it : adj)
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
    Graph<string> g{};

    while(cin >> p >> t) {
        if (p == 0 && t == 0)
            break;

        g.clear();

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