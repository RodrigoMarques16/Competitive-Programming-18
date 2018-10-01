#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef multiset<int>::iterator soldier;

int main() {

    int n, b, sg, sb, power;
    multiset<int> green_army, blue_army;
    vector<int> green_survivors, blue_survivors;
    bool line_flag = false;
    cin >> n;

    while(n--) {

        cin >> b >> sg >> sb;

        green_army.clear();
        blue_army.clear();

        for(int i = 0; i < sg; i++) {
            cin >> power;
            green_army.insert(power);
        }
        for(int i = 0; i < sb; i++)  {
            cin >> power;
            blue_army.insert(power);
        }

        while(!green_army.empty() && !blue_army.empty()) {
            
            int fights = min(b, 
                         min((int) green_army.size(), 
                             (int) blue_army.size()));   

            green_survivors.clear();
            blue_survivors.clear();

            for(int i = 0; i < fights; i++) {
                soldier green = --green_army.end();
                soldier blue = --blue_army.end();

                int gp = *green, bp = *blue;

                green_army.erase(green);
                blue_army.erase(blue);

                if (gp > bp) {
                    green_survivors.push_back(gp-bp);
                }
                else if (bp > gp){
                    blue_survivors.push_back(bp-gp);
                }
            }

            for(auto it : green_survivors)
                green_army.insert(it);
            for(auto it : blue_survivors)
                blue_army.insert(it);

        }

        if (line_flag)
            cout << '\n';
        line_flag = true;

        if (green_army.empty() && blue_army.empty()) {
            cout << "green and blue died\n";
        }
        else if (green_army.empty() && !blue_army.empty()) {
            cout << "blue wins\n";
            for(multiset<int>::reverse_iterator it = blue_army.rbegin(); it != blue_army.rend(); it++) {
                cout << *it << endl;
            }
        } 
        else if (!green_army.empty() && blue_army.empty()) {
            cout << "green wins\n";
            for(multiset<int>::reverse_iterator it = green_army.rbegin(); it != green_army.rend(); it++) {
                cout << *it << endl;
            }
        }
        
    }

    return 0;
}