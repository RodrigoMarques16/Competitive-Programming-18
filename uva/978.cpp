#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef multiset<int>::iterator soldier;

// 978 - Lemmings Battle!
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=919
//
// Simulate a battle between two armies
//
// Keep track of the armies using a multiset. 
// For each round, take the soldiers to battle out from the multiset and save the survivors
// in a vector to add back to the set when the round is over.


int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    bool line_flag = false;
    
    cin >> n;

    while(n--) {

        int b, sg, sb, power;
        multiset<int, std::greater<int>> green_army, blue_army;

        cin >> b >> sg >> sb;   

        for(int i = 0; i < sg; i++) {
            cin >> power;
            green_army.insert(power);
        }
        for(int i = 0; i < sb; i++)  {
            cin >> power;
            blue_army.insert(power);
        }

        while(!green_army.empty() && !blue_army.empty()) {
            
            // There can only be as many fights in a round as battlegrounds or
            // as many soldiers in the smallest army

            int fights = min(b, 
                         min((int) green_army.size(), 
                             (int) blue_army.size()));   

            // Keep track of the survivors from this round in a vector so we can
            // add them back to their armies at the end of the round

            vector<int> green_survivors, blue_survivors;

            for(int i = 0; i < fights; i++) {

                // The strongest soldiers are always at the beginning of the multiset.

                soldier green = green_army.begin();
                soldier blue = blue_army.begin();

                int gp = *green, bp = *blue;

                green_army.erase(green);
                blue_army.erase(blue);

                // Calculate the outcome of the battle, the soldier with the highest
                // power survives.
                
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
            for(auto it : blue_army)
                cout << it << endl;
        } 
        else if (!green_army.empty() && blue_army.empty()) {
            cout << "green wins\n";
            for(auto it : green_army)
                cout << it << endl;
        }
        
    }

    return 0;
}