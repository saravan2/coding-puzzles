#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void dumpMultiplicationTable(int n, int till) {
    for (int i = 1; i <= till; i++) {
        cout << n << " x " << i << " = " << (n*i) << endl;
    }
}

int main(){
    int n;
    cin >> n;
    if (n < 2 || n > 20) {
        cout << "Invalid input" << endl;
        return -1;
    }
    dumpMultiplicationTable(n, 10);
    return 0;
}

