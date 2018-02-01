#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    double mealCost;
    int tipPercent;
    int taxPercent;
    
    cin >> mealCost;
    cin >> tipPercent;
    cin >> taxPercent;
    
    double tip = ((1.0 * tipPercent) * mealCost)/100;
    double tax = ((1.0 * taxPercent) * mealCost)/100;
    double totalCost = mealCost + tip + tax;
    int tc = round(totalCost);
    cout << "The total meal cost is " << tc << " dollars." << endl;
    return 0;
}
