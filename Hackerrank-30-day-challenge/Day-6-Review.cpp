#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void split(string &line) {
    string even, odd;
    if (!line.size()) {
        cout << "" << endl;
    } else {
        for (int i = 0; i < line.size(); i++) {
            if (i & 0x1) {
                odd = odd + line[i];
            } else {
                even = even + line[i];
            }
        }
        cout << even << " " << odd << endl;
    }
}

int main() {
    int T;
    cin >> T;
    if (T < 1 || T > 10) {
        cout << "Invalid number of Test cases" << endl;
        return -1;
    }
    cin.ignore();
    string line;
    for (int i = 0; i < T; i++) {
        getline(cin, line);
        split(line);
    }
    return 0;
}

