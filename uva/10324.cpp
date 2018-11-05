#include <iostream>
#include <vector>

#define DEBUG(x) cout << #x ": " << x << endl;

using namespace std;

int main() {

    string str;

    int n, case_number = 1;
    while(cin >> str) {
        cin >> n;
        vector<int> ac(str.length()+5, 0);

        int i = 1;
        for (auto c : str) {
            ac[i] = ac[i-1];
            if (c == '1') {
                ac[i] = ac[i-1] + 1;
            }
            i++;
        }
        cout << "Case " << case_number << ":" << endl;
        for(int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            int x = min(a,b);
            int y = max(a,b);
            int count =  ac[y+1] - ac[x];
            if (count == y-x+1 or count == 0)
                cout << "Yes\n";
            else cout << "No\n";
        }
        case_number++;
    }
    return 0;
}