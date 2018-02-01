#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    map<string, int> phoneBook;
    cin >> N;
    cin.ignore();
    string line;
    while (N) {
        stringstream ss;
        string key;
        int value;
        getline(cin, line);
        ss << line;
        ss >> key;
        ss >> value;
        phoneBook.insert(pair<string, int>(key, value));
        N--;
    }
    while (getline(cin, line)) {
        map<string, int>::iterator it = phoneBook.find(line);
        if (it != phoneBook.end()) {
            cout << line <<"=" << it->second << endl;
        } else {
            cout << "Not found" << endl;
        }
    }
    return 0;
}
