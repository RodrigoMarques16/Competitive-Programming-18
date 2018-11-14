#include <cstdio>
#include <vector>
#include <algorithm>

// UVA 166 - Making Change
//
// intro
//
// 


#define DEBUG(x) cout << #x << ": " << x << endl;
#define NCOINS 6
#define MAX 150
#define INF 9999

using namespace std;

const vector<int> coin_value { 1, 2, 4, 10, 20, 40 };
vector<int> coins(6);
vector<int> dp(MAX+5, INF);
vector<int> shop(MAX+5, 0);

// Infinite supply, standard greedy algorithm
// if uva used an up to date standard this could be constexpr
void doShopkeeper() {
    for(int i = 1; i < 41; i++) {
        int change = i;
        for(int j = 5; j >= 0 && change > 0; j--) {
            shop[i] += change / coin_value[j];
            change  %= coin_value[j];
        }
    }
}

// Limited supply
void doClient(int value) {
    dp[0] = 0;
    for(int i = 0; i < 6; i++) {
        int c = coins[i];
        while(c) {
            // For each coin, iterate through all the possible amounts we could get back as change
            for(int change = value + 40; change >= coin_value[i]; change--) {
                int remaining = change - coin_value[i];
                // If we know the minimum coins for the remaining amount we can use it
                // to calculate the minimum for the current amount
                if (dp[remaining] != INF)
                    dp[change] = std::min(dp[change], dp[remaining]+1);
            }
            c--;
        }   
    }
}

int main() {
    doShopkeeper();

    while(true) {
        std::fill(dp.begin(), dp.end(), INF);

        int available = 0;
        for(int i = 0; i < NCOINS; i++) {
            scanf("%d", &coins[i]);
            available += coins[i] * coin_value[i];
        }

        // no more test cases
        if (available == 0) break;

        // value to pay, converted to cents
        double v;
        scanf("%lf", &v); 
        v *= 20;
        int value = (int) v; 

        doClient(value);

        int mincoins = INF;
        // Iterate through all possible payments and calculate the number of coins
        for (int pay = value; pay <= value + 40; pay++) {
            if (dp[pay] != INF) {

                // If we're overpaying, add the coins we get to the total
                if (pay > value)
                    dp[pay] += shop[pay - value];

                mincoins = std::min(mincoins, dp[pay]);
            }
        }

        printf("%3d\n", mincoins);
    }

    return 0;
}
