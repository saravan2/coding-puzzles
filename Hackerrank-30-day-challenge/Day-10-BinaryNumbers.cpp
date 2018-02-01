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

#define BYTE 8

int main(){
    int n;
    cin >> n;
    int totalCount, currentCount;
    totalCount = currentCount = 0;
    for (int i = 0; i < (sizeof(int) * BYTE); i++) {
        if(n & (1 << i)) {
            currentCount++;
        } else {
            currentCount = 0;
        }
        if (currentCount > totalCount) {
            totalCount = currentCount;
        }
    }
    cout << totalCount << endl;
    return 0;
}
