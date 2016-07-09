#include<sstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// Recursive solution
// Brute force, not scalable, O(2^N)
void recursivePowerSetUsingString(string number, string sofar) {
	if (number.empty())
		cout << "{" << sofar << "}" << endl;
	else {
		if (sofar.empty())
			recursivePowerSetUsingString(number.substr(1, number.length()), sofar + number[0]);
		else
			recursivePowerSetUsingString(number.substr(1, number.length()), sofar + "," + number[0]);
		recursivePowerSetUsingString(number.substr(1, number.length()), sofar);
	}
	
}

void recursivePowerSet(vector<int> &set, string sofar, int pos) {
	if (pos >= set.size())
		cout << "{" << sofar << "}" << endl;
	else {
		// Valuable lesson learnt, we cannot add an integer to STL string
		// We have to use stringstream
		stringstream elm;
		elm<<set[pos];
		if (sofar.empty())
			recursivePowerSet(set, sofar+elm.str(), pos + 1);
		else
			recursivePowerSet(set, sofar+","+elm.str(), pos + 1);
		recursivePowerSet(set, sofar, pos + 1);
	}
}

void fillVector(vector<int> &set, int n) {
	set.clear();
	for (int i = 0; i < n; i++) 
		set.push_back(i+1);
}

void printVector(vector<int> &set) {
	for (int i = 0; i < set.size(); i++)
		cout << set[i] << endl;
}

// Iterative solution

int main() {
	cout << endl << "Using Strings as input :" << endl;
	recursivePowerSetUsingString("1234", "");
	vector<int> set;
	fillVector(set, 4);
	cout << endl << "Using set as input : " << endl;
	recursivePowerSet(set,"", 0);
//	iterativePowerSet(4);
	return 0;
}
