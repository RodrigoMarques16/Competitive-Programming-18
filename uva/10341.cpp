#include <iostream>
#include <cmath>
#include <iomanip>

#define EPS 1e-15

using namespace std;

int p, q, r, s, t, u;

double f(double x) {
    return p * exp(-x) + q * sin(x) 
         + r * cos(x)  + s * tan(x) 
         + t * x * x + u;
}

double binary_search(double low, double high) {

    double mid = low + (high - low) / 2;

    if (high - low <= EPS)
        return  mid;

    if (f(low) * f(mid) <= 0)
        return binary_search(low, mid);
    else
        return binary_search(mid, high); 

}

int main() {

    while(cin >> p >> q >> r >> s >> t >> u) {
        
        if (f(0) * f(1) > 0) {
            cout << "No solution\n";
        }
        else {
            cout << std::fixed
                 << std::setprecision(4) 
                 << binary_search(0,1) 
                 << endl;
        }
    }

    return 0;
}