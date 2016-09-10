#include<iostream>
#include<string>
using namespace std;

// O(2^(n-1))
// Surprisingly no duplicates
void generateInOrderListing(string n, string prefix) {
	// Prefix + enclosing remaining number within parentheses is valid solution
	cout << prefix + "(" + n + ")" << endl;
	// i(1) < n.length prevents us from repeating (prefix)(remaining) which has 
	// already been done earlier in the function.
	for (int i = 1; i < n.length(); i++) {
		// Split the remaining number to form newer prefixes (bigger) for recursive calls.
		string newPrefix = prefix + "(" + n.substr(0,i) + ")";
		// Remaining number and newer prefix are passed as argument to the recursive call
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
