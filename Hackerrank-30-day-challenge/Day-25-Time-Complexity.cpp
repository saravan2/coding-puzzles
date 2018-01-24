#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool isPrime(unsigned int val) {
    
    if (val == 1) {
        return false;
    } else if (val == 2) {
        return true;
    }
    
    if (!(val & 0x1)) {
        return false;
    }
    
    for (unsigned int i = 3UL; (i*i) <= val; i = i+2) {
        if (!(val % i))
            return false;
    }
    return true;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    unsigned int val;
    cin >> N;
    while (N) {
        cin >> val;
        if (isPrime(val)) {
            cout << "Prime" << endl;
        } else {
            cout << "Not prime" << endl;
        }
        N--;
    }
    return 0;
}
