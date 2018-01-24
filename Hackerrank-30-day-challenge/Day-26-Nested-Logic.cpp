#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;


int main() {
    string line, line1;
    int eDay, eMonth, eYear, aDay, aMonth, aYear, fine = 0;
    stringstream ss, ss1;  
    getline(cin, line);
    ss << line;
    ss >> aDay;
    ss >> aMonth;
    ss >> aYear;
    line.clear();
    ss.clear();
    ss.str(string());
    getline(cin, line);
    ss << line;
    ss >> eDay;
    ss >> eMonth;
    ss >> eYear;
    
    if (aYear > eYear) {
        fine = 10000;
        cout << fine << endl;
    } else if ((aYear == eYear) && (aMonth > eMonth)){
        fine = 500 * (aMonth - eMonth);
        cout << fine << endl;
    } else if ((aYear == eYear) && (aMonth == eMonth) && (aDay > eDay)) {
        fine = 15 * (aDay - eDay);
        cout << fine << endl;
    } else {
        cout << fine << endl;
    }
    
    return 0;
}
