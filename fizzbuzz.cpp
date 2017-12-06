// Works on C++ 14
#include<iostream>
#include<vector>
#include<string>
#include<limits>
using namespace std;

#define ERROR -1
#define SUCCESS 0

// Assumes that newTerm is >=7, odd and is not a multiple of 3 or 5
bool isPrimeOptimized(unsigned long long newTerm) {
	unsigned long long divby3Tracker = 2;
	unsigned long long divby5Tracker = 1;
	for (unsigned long long i = 7ULL; (i*i) <= newTerm; i=i+2, divby3Tracker++, divby5Tracker++) {
		// Save CPU cycles avoiding mod operations on newTerm
		// (can be very large unsigned long long number)
		// which are destined to fail   
		if ((divby3Tracker == 3) || (divby5Tracker == 5)) {
			if (divby3Tracker ==3) {
				divby3Tracker = 0;
			}
			if (divby5Tracker == 5) {
				divby5Tracker = 0;
			}
			continue;
		}
                if((newTerm % i) == 0) {
                        return false;
                }
        }
        return true;
}

void printNewTerm(unsigned long long newTerm) {
	enum printTypes { undefined, regular, divby3, divby5, divby15, prime };
	printTypes now = undefined;
	if (newTerm <= 1ULL) {
		now = regular;
	} else if ((newTerm == 2ULL) ||
		(newTerm == 3ULL) ||
		(newTerm == 5ULL)){
		now = prime;
	} else if ((newTerm % 15ULL) == 0) {
		now = divby15;
	} else if ((newTerm % 5ULL) == 0) {
		now = divby5;
	} else if ((newTerm % 3ULL) == 0) {
		now = divby3;
	} else if ((newTerm & 0x1ULL) == 0) {
		now = regular;
	} else if (isPrimeOptimized(newTerm)) {
		now = prime;
	} else {
		now = regular;
	}

	switch(now) {
		case regular:
			cout << newTerm << " ";
			break;
		case divby3:
			cout << "Buzz ";
			break;
		case divby5:
			cout << "Fizz ";
			break;
		case divby15:
			cout << "FizzBUzz ";
			break;
		case prime:
			cout <<"BuzzFizz ";
			break;
	}
}


int generateSequence(unsigned long long N) {
	if (N < 1) {
		return ERROR;
	} 
	unsigned long long newTerm, p1 = 0, p2 = 1;
	for (unsigned long long i = 1; i <= N; i++) {
		if (i == 1) {
			printNewTerm(p1);
			continue;
		} else if (i == 2) {
			printNewTerm(p2);
			continue;
		} else {
			if (p2 > (numeric_limits<unsigned long long>::max() - p1)) {
				cout << endl << "Unsigned long long datatype overflowed, unable to continue ... Aborting " << endl;
				return ERROR;
			}
			newTerm = p1 + p2;
			printNewTerm(newTerm);
			p1 = p2;
			p2 = newTerm;
		}
	}
	cout << endl;
	return SUCCESS;
}

void usage(vector<string>& args) {
	cout << "Proper usage : " << args[0] << " <# of Fibnocci sequence>" << endl;
}

int main(int argc, char* argv[]) {
	vector<string> args(argv, argv + argc);
	if ((args.size() == 1) || (args.size() > 2)) {
		usage(args);
		return ERROR;
	}
	unsigned long long N = stoull(args[1]);
	return generateSequence(N);
}
