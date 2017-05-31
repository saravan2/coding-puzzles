//Credits : Jackson Gabbard www.jg.gg
//g++ -g -std=c++11 -o pg permutationGenerator.cpp
#include<iostream>
#include<vector>
#include <sstream>

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
		if (completed == maxPermutations)
			return vector<int>{};

		if (!base.size()) {
			for (int i=0; i<size; i++) {
				base.push_back(i+1);
			}
			completed++;
			return base;
		}

		// Finding the first decrement
		vector<int>::iterator decr = (base.end()-2);
		while ((decr >= base.begin()) && (*decr > *(decr+1))) {

			// Reduntant as completed == maxPermutations would screen this case

			// No further permutation is possible
			// Valuable lesson learnt, decr could get below begin()
			// Outside of this while loop, so catch it inside.
			if (decr == base.begin())
				return vector<int>{};
			decr--;
		}

		// Finding the next biggest element
		vector<int>::iterator nextBig = (base.end()-1);
		while ((nextBig >= base.begin()) && (*decr > *nextBig))
			nextBig--;
		
		// Swapping decr and next biggest element
		swap(decr, nextBig);

		// Reversing the rest of the suffix from decr+1
		vector<int>::iterator left = decr+1;
		vector<int>::iterator right = (base.end()-1);
		while (left < right) {
			swap(left, right);
			left++;
			right--;
		}

		completed++;	

		return base;
	}
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

	cout << "Max # of permuations is " << p.maxNumberOfPermutations() << ". Number of permutations left is " << p.numberOfPermutationsLeft() << endl;

	vector<int> result;
	while (true) {
		result = p();
		if (!result.size())
			break;
		printResult(result);
	}	

	return 0;
		 
}
