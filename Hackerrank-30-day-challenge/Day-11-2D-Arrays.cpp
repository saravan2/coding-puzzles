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
using namespace std;

#define HG_ROW_WIDTH 3
#define HG_COLUMN_WIDTH 3
int getHGValue(vector< vector<int> >& arr, int rn, int cn) {
    vector< vector<int> >::iterator row;
    vector<int>::iterator col;
    int hgLevel = 1;
    int hgValue = 0;
    while (hgLevel <= HG_ROW_WIDTH) {
        if (hgLevel & 0x1) {
            for (int i = 0; i < HG_COLUMN_WIDTH; i++) {
                hgValue += arr[rn][cn+i];
            }
        } else {
            hgValue += arr[rn][cn + 1];
        }
        if (hgLevel < 3) {
            rn++;
            hgLevel++;
        } else {
            break;
        }
    }
    return hgValue;
}
void findLargestHourGlassInMatrix(vector< vector<int> >& arr) {
    int maxSoFar = numeric_limits<int>::min();
    for (int rn = 0; (rn + HG_ROW_WIDTH - 1) < arr.size(); rn++) {
        for (int cn = 0; (cn + HG_COLUMN_WIDTH - 1) < arr[rn].size(); cn++) {
            int currentHGValue = getHGValue(arr, rn, cn);
            if (maxSoFar < currentHGValue) {
                maxSoFar = currentHGValue;
            }
        }
    }
    cout << maxSoFar << endl;
}

int main(){
    vector< vector<int> > arr(6,vector<int>(6));
    for(int arr_i = 0;arr_i < 6;arr_i++){
       for(int arr_j = 0;arr_j < 6;arr_j++){
          cin >> arr[arr_i][arr_j];
       }
    }
    findLargestHourGlassInMatrix(arr);
    return 0;
}

