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
	unsigned int divby3Tracker = 2;
	unsigned int divby5Tracker = 1;
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

/*
Runtime :
saravanand@SJCLSARAVANA01 ~/coding-puzzles
$ g++ -O3 -o fizz fizzbuzz.cpp

saravanand@SJCLSARAVANA01 ~/coding-puzzles
$ time ./fizz.exe 100
0 1 1 BuzzFizz BuzzFizz BuzzFizz 8 BuzzFizz Buzz 34 Fizz BuzzFizz Buzz BuzzFizz 377 Fizz Buzz BuzzFizz 2584 4181 FizzBUzz 10946 17711 BuzzFizz Buzz Fizz 121393 196418 Buzz BuzzFizz Fizz 1346269 Buzz 3524578 5702887 Fizz Buzz 24157817 39088169 63245986 FizzBUzz 165580141 267914296 BuzzFizz Buzz Fizz 1836311903 BuzzFizz Buzz 7778742049 Fizz 20365011074 Buzz 53316291173 86267571272 Fizz Buzz 365435296162 591286729879 956722026041 FizzBUzz 2504730781961 4052739537881 6557470319842 Buzz Fizz 27777890035288 44945570212853 Buzz 117669030460994 Fizz 308061521170129 Buzz 806515533049393 1304969544928657 Fizz Buzz 5527939700884757 8944394323791464 14472334024676221 FizzBUzz 37889062373143906 61305790721611591 BuzzFizz Buzz Fizz 420196140727489673 679891637638612258 Buzz 1779979416004714189 Fizz 4660046610375530309 Buzz 12200160415121876738
Unsigned long long datatype overflowed, unable to continue ... Aborting

real    0m1.047s
user    0m1.014s
sys     0m0.015s

 */
