#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// This sequence gets big very quickly to blow up native datatypes, hence using strings is a necessity 

string intToString(int n) {
	stringstream ss;
	ss << n;
	return ss.str();	
}

string getNext(string prev) {
	string next="";
	if (prev.empty())
		return next;

	vector<int> prevElement;
	for (int i = 0; i < prev.size(); i++) {
		prevElement.push_back(prev[i] - 48);
	}

#if 0
	int count = 0;
	int val = 0;
	for (int i = 0; i < prevElement.size(); i++) {
		if (i == 0) {
			val = prevElement[i];
			count = 1;
			continue;
		}
#else
	int count = 1;
	int val = prevElement[0];
	for (int i = 1; i < prevElement.size(); i++) {
#endif
		if (val != prevElement[i]) {
			next = next + intToString(count) + intToString(val);
			val = prevElement[i];
			count = 1;
		} else {
			count++;
		}
	}

#if 0
	if (count > 0) {
		next = next + intToString(count) + intToString(val);
	}
#else
	next = next + intToString(count) + intToString(val);
#endif
	

	return next;
}

void countAndSay(int n) {
	if (n <= 0) {
		cout << "" << endl;
		return;
	}	

	if (n == 1) {
		cout << "1" << endl;
		return;
	}

	string prev="1";
	string seq = prev;
	for (int i = 1; i < n ; i++) {
		string next = getNext(prev);
		seq = seq + "," + next;
		prev = next;
	}

	cout << seq << endl;
}

int main(int argc, char *argv[]) {
	int n = 0;
	if (argc > 1)
		n = atoi(argv[1]);
	countAndSay(n);	
	return 0;
}
