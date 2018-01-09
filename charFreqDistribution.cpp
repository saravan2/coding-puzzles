#include <iostream>
#include <map>
#include <set>
#include <climits>
using namespace std;

map<char, int> parseString(string input) {
    map<char, int> output;
    for (unsigned int i=0; i < input.length(); i++) {
        if (output.find(input[i]) == output.end()) {
            output[input[i]] = 1;
        } else {
            output[input[i]] += 1;
        }
    }
    return output;
}

int main(int argc, char *argv[]){
    string input;
    getline(cin, input);
    map<char, int> frequency = parseString(input);
    set<char> mostCommon;
    set<char> leastCommon;
    int mcSoFar = 0;
    int lcSoFar = INT_MAX;
    for (auto i = frequency.begin(); i != frequency.end(); i++) {
        cout << i->first <<  " frequency " << i->second << endl;
        if (i->second >= mcSoFar) {
            if (i->second > mcSoFar) {
                mostCommon.clear(); 
                mostCommon.insert(i->first);
                mcSoFar = i->second;
            } else {
                mostCommon.insert(i->first);
            }
        }
        if (i->second <= lcSoFar) {
            if (i->second < lcSoFar) {
                leastCommon.clear();
                leastCommon.insert(i->first);
                lcSoFar = i->second;
            } else {
                leastCommon.insert(i->first);
            }
        }
    }
    cout << "Most Common characters : ";
    for (auto i = mostCommon.begin(); i != mostCommon.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    cout << "Least Common characters : ";
    for (auto i = leastCommon.begin(); i != leastCommon.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    return 0;
}
