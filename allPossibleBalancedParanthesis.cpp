#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;

// Read about catalan numbers
// Formula (2n)!/((n+1)!n!)
void generate(int left, int right, string soFar) {
	// Common Coding error left == right == 0
	// when left != right, then left == right will return 0 which will be compared with 0
	// and our misguided condition will return true
	 
	// We have exhausted all available left and right paranthesis, lets print our 
	// constructed solution so far
	if (left == 0 && right == 0) {
		cout << soFar << endl;
	} else {
		// The invariant for balanced parentheses is that at any point in our construction
		// the # left parantheses should be greater or equal than the # right parentheses
		// So that we may avoid constructing ()) or )()
		if (left > 0)
			generate((left - 1), right, soFar + "(");
		if ((right > 0) && (right > left))
			generate(left, (right - 1), soFar + ")");
	}
}

void generateParanthesis(int n) {
	string soFar = "";
	generate(n, n, soFar);
}

int main(int argc, char ** argv) {
	int n = 3;
	if (argc > 1)
		n = atoi(argv[1]);
	cout << endl << "All possible paranthesis combination in a set of " << n << endl;
	generateParanthesis(n);
	return 0;
}
