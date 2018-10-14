#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// 11995 - I Can Guess the Data Structure
//
// Given a sequence of push and pop commands, determine if they correspond to a set,
// queue or priority queue.
//
// Using the STL's data structures we can keep track of which structure is valid
// for the given input.
//
// Time: O(n * insertion time)
// Space: O(n)

int main() {
    
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while(cin >> n) {
        
        stack<int> s;
        queue<int> q;
        priority_queue<int, vector<int>, std::less<int>> p;
        int isQueue, isPQueue, isStack;

        isQueue = isPQueue = isStack = 1;
        
        while(n--) {
            int command, value;
            cin >> command >> value;

            if (command == 1) {
                s.push(value);
                p.push(value);
                q.push(value);    

            } else {
                
                // Ignore pop commands when the structures are empty
                
                if (q.empty()) {
                    isQueue = isPQueue = isStack = 0;
                    continue;
                }

                // Here we check if the first element of the structures is the same 
                // as the one read from input
                // We need to check empty() before trying to access the data!

                isQueue  = isQueue  && (q.front() == value);
                isPQueue = isPQueue && (p.top()   == value);
                isStack  = isStack  && (s.top()   == value);

                q.pop();
                p.pop();   
                s.pop();
            }

        }

        // cool bit shifts so we can use a switch for the output

        int result = isQueue + (isPQueue << 1) + (isStack << 2);

        switch(result){
            case 0: {
                cout << "impossible\n";
                break;
            }
            case 1: {
                cout << "queue\n";
                break;
            }
            case 2: {
                cout << "priority queue\n";
                break;
            }
            case 4: {
                cout << "stack\n";
                break;
            }
            default: {
                cout << "not sure\n";
                break;
            }
        }

    }

    return 0;
}
