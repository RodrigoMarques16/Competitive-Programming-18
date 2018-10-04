#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main() {
    
    int n;

    while(cin >> n) {
        queue<int> q;
        priority_queue<int, vector<int>, std::less<int>> p;
        stack<int> s;
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

                isQueue  = isQueue  && (!q.empty()) && (q.front() == value);
                isPQueue = isPQueue && (!p.empty()) && (p.top() == value);
                isStack  = isStack  && (!s.empty()) && (s.top() == value);

                if (q.empty())
                    continue;

                q.pop();
                p.pop();   
                s.pop();
            }

        }

        int result = isQueue + (isPQueue << 1) + (isStack  << 2);

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