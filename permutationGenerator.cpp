//Credits : Jackson Gabbard www.jg.gg, Geek for Geeks.
//g++ -g -std=c++11 -o pg permutationGenerator.cpp
// For string with no duplicates, the complexity is O(n*n!), as we can
// afford to reverse the suffix blindly.
// For string with duplicates, the complexity to generate all distinct 
// permutations is O(nlogn*n!). Note that we have to sort the suffix 
// containing duplicates after swap, to produce all distinct permutations. 
// Both approaches require base string to be sorted to produce lexicographically
// ordered generations.
// Brute force backtracking recursive method exists whose complexity is O(n*n!)
// which is not scalable and requires addtional set datastructure to filter
// duplicate permutations when the string is known to contain duplicates.
#include<iostream>
#include<vector>
#include <sstream>
#include<algorithm>

using namespace std;
class permutationGen {
	private:
	vector<int> base;
	unsigned int size;
	unsigned int maxPermutations;
	unsigned int completed;
	void swap(const vector<int>::iterator t1, const vector<int>::iterator t2) {
		int temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
	public:
	permutationGen(unsigned int _size=4):size(_size) {
		completed = 0;
		maxPermutations = maxNumberOfPermutations();	
	}
	vector<int> operator() (){
//		if (completed == maxPermutations)
//			return vector<int>{};

		if (!base.size()) {
			for (int i=0; i<size; i++) {
#if 0
				// Code to add duplicates.
				if (i < 2)
					base.push_back(1);
				else if (i >= size-3)
					base.push_back(size-1);
				else
					base.push_back(i+1);
#endif
				base.push_back(i+1);
			}
			sort(base.begin(), base.end());
			completed++;
			return base;
		}

		// Finding the first decrement
		vector<int>::iterator decr = (base.end()-2);
		while (decr >= base.begin()) {
			if (*decr < *(decr+1)) {
				break;
			}

			// Reduntant as completed == maxPermutations would screen this case
			// However as we do not accurately calculate maxPermutations
			// in strings with duplicates, we eventually hit this
			// conditional check.

			// No further permutation is possible
			// Valuable lesson learnt, decr could get below begin()
			// Outside of this while loop, so catch it inside.
			if (decr == base.begin())
				return vector<int>{};
			decr--;
		}

		// Finding the closest big element in the suffix
		vector<int>::iterator suffix = (decr+1);
		vector<int>::iterator nextBig = suffix;
		while (suffix <= base.end()) {
			if ((*suffix > *decr) && (*suffix < *nextBig))
				nextBig = suffix;
			suffix++;
		}
		
		// Swapping decr and next biggest element
		swap(decr, nextBig);

		// *If the input contains duplicates, we have to sort
		// the suffix to produce distinct permutations !*
		vector<int>::iterator left = decr+1;
/*
		// Reversing the rest of the suffix from decr+1
		// This strategy works iff there are no duplicates.
		vector<int>::iterator right = (base.end()-1);
		while (left < right) {
			swap(left, right);
			left++;
			right--;
		}
*/
		sort(left, base.end());
		completed++;	

		return base;
	}
	/* Fails miserably when string has duplicates */
	unsigned int maxNumberOfPermutations() {
		unsigned int result = 0;
		if (size) {
			result = 1;
			for (int i=0; i<size; i++) {
				result *= (i+1);
			}
		}
		return result;
	}

	unsigned int numberOfPermutationsLeft() {
		return (maxPermutations - completed);
	}

};	

void printResult(const vector<int>& result) {
	unsigned int size = result.size();
	if (size) {
		for (int i=0; i < size; i++) {
			cout << result[i];
			if ((i+1) != size)
				cout << ",";
		}
		cout << endl;
	}
}
		

int main(int argc, char* argv[]) {
	permutationGen p;
	if (argc > 1) {
		istringstream ss(argv[1]);
		unsigned int upto;
		if (ss >> upto) {
			permutationGen t(upto);
			p = t;
		} else {
			cout << "Invalid parameter, overriding with defaults" << endl;
		}
	} 

//	cout << "Max # of permuations is " << p.maxNumberOfPermutations() << ". Number of permutations left is " << p.numberOfPermutationsLeft() << endl;

	vector<int> result;
	while (true) {
		result = p();
		if (!result.size())
			break;
		printResult(result);
	}	

	return 0;
		 
}
