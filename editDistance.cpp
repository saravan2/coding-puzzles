#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstdbool>
using namespace std;

int min(int x,int y,int z) {
    return min(min(x, y), z);
}

int naiveEditDistance(string str1, string str2, int m, int n) {
    if (m == 0)
        return n;
    
    if (n == 0)
        return n;
        
    if (str1[m-1] == str2[n-1])
        return naiveEditDistance(str1, str2, (m-1), (n-1));
        
    return 1 +  min(naiveEditDistance(str1, str2, m-1, n),
                    naiveEditDistance(str1, str2, m, n-1),
                    naiveEditDistance(str1, str2, m-1, n-1)
                    );
}

int dpEditDistance(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    int **s = new int*[m+1];
    for (int i = 0; i < (m+1) ; i++) {
        s[i] = new int[n+1];
    }
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) { 
                s[i][j] = j;
            } else if (j == 0) {
                s[i][j] = i;
            } else if (str1[i] == str2[j]) {
                s[i][j] = s[i-1][j-1];
            } else {
                s[i][j] = 1 + min(  s[i-1][j],
                                    s[i][j-1],
                                    s[i-1][j-1]
                                );
            }
        }
    }
    return s[m][n];
}

bool isSingleEdit(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    
    if (abs(m-n) > 1)
        return false;
        
    int i = 0;
    int j = 0;
    int count = 0;
    while (i < m && j < n) {
        if (str1[i] == str2[j]) {
            i++;
            j++;
        } else {
            if (count == 1)
                return false;
            count++;
            if(m > n) {
                i++;
            } else if (n > m) {
                j++;
            } else {
                i++;
                j++;
            }
        }
    }    
    if  (i < m || j < n)
        count++;
        
    return (count == 1);
}

int main(int argc, char* argv[])
{
  std::string str1, str2;
  str1 = "sunday";
  str2 = "saturday";
  cout <<naiveEditDistance(str1, str2, str1.length(), str2.length()) << endl;
  cout << dpEditDistance(str1, str2) << endl;
  if (isSingleEdit("bus", "bust")) {
      cout << "Yes" << endl;
  } else {
      cout << "No" << endl;
  }
}

