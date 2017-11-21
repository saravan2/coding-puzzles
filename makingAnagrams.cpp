/*
Alice is taking a cryptography class and finding anagrams to be very useful. We consider two strings to be anagrams of each other if the first string's letters can be rearranged to form the second string. In other words, both strings must contain the same exact letters in the same exact frequency For example, bacdc and dcbac are anagrams, but bacdc and dcbad are not.

Alice decides on an encryption scheme involving two large strings where encryption is dependent on the minimum number of character deletions required to make the two strings anagrams. Can you help her find this number?

Given two strings, and , that may or may not be of the same length, determine the minimum number of character deletions required to make and anagrams. Any characters can be deleted from either of the strings.

This challenge is also available in the following translations:

    Chinese
    Russian

Input Format

The first line contains a single string, .
The second line contains a single string, .

Constraints

    It is guaranteed that and consist of lowercase English alphabetic letters (i.e., through ).

Output Format

Print a single integer denoting the number of characters you must delete to make the two strings anagrams of each other.

Sample Input

cde
abc

Sample Output

4

Explanation

We delete the following characters from our two strings to turn them into anagrams of each other:

    Remove d and e from cde to get c.
    Remove a and b from abc to get c.

We must delete characters to make both strings anagrams, so we print on a new line.
*/

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

int number_needed(string a, string b) {
    if (a.empty())
        return b.size();
    if (b.empty())
        return a.size();
    
   map<char, int> distributionOfA;
   for (int i=0; i < a.size(); i++) {
       distributionOfA[a[i]] += 1;
   }
   std::map<char,int>::iterator it;
   int deletions = 0;
   for (int i=0; i < b.size(); i++) {
       std::map<char,int>::iterator it = distributionOfA.find(b[i]);
       if (it == distributionOfA.end()) {
           deletions++;
       } else {
           it->second -= 1;
           if (it->second < 0)
               deletions++;
       }
   }
   for (std::map<char,int>::iterator it = distributionOfA.begin(); it != distributionOfA.end(); it++) {
       if (it->second > 0) {
           deletions += it->second;
       }
   }
   return deletions;
}

int main(){
    string a;
    cin >> a;
    string b;
    cin >> b;
    cout << number_needed(a, b) << endl;
    return 0;
}
