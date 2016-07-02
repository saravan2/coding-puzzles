#include<iostream>
#include<string>
using namespace std;

void generateInOrderListing(string n, string prefix) {
	cout << prefix + "(" + n + ")" << endl;
	for (int i = 1; i < n.length(); i++) {
		string newPrefix = prefix + "(" + n.substr(0,i) + ")";
		generateInOrderListing(n.substr(i), newPrefix);
	}
}

void inOrderListing(string n) {
	generateInOrderListing(n, "");
}

int main() {
	inOrderListing("1234");
	return 0;
}
