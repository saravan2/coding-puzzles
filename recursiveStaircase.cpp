//Credits : CS Dojo
#include<iostream>
#include<vector>
using namespace std;
// Similar to Fibnocci
// n can only be 0 or +ve
// 1 or 2 steps at a time
int naiveNumWaysToClimb(int n) {

	if (n == 0 || n == 1)
		return 1;

	return naiveNumWaysToClimb(n-1) + naiveNumWaysToClimb(n-2);
}

// Sane DP solution
// 1 or 2 steps at a time
// Space complexity O(n)
// Time complexity O(n)
int numWaysToClimb(int n) {
        if (n == 0 || n == 1)
                return 1;
	int *arr = (int *)calloc(n+1, sizeof(int));
	arr[0] = 1;
	arr[1] = 1;
	for (int i=2; i<=n; i++) {
		arr[i] = arr[i-1] + arr[i-2];
	}
	int result = arr[n];
	free(arr);
	return result;
}

// Sane DP with constant space complexity
// For 1 or 2 steps
int numWaysToClimbEff(int n) {
	if (n == 0 || n == 1)
                return 1;
	int pprev = 1;
	int prev = 1;
	int total = 0;
	for (int i=2; i<=n; i++) {
		total = prev + pprev;
		pprev = prev;
		prev = total;
	}
	return total;
}

// Set of step jumps
int naiveNumWaysToClimbWithSetOfJumps(int n, vector<int> &steps) {
	if (n == 0) return 1;
	int total = 0;
	for (int i = 0; i < steps.size(); i++) {
		if (n - steps[i] >= 0) {
			total += naiveNumWaysToClimbWithSetOfJumps(n-steps[i], steps);
		}
	}
	return total;
}

// Set of step jumps
int numWaysToClimbWithSetOfJumps(int n, vector<int> &steps) {
        if (n == 0) return 1;
        int *arr = (int *)calloc(n+1, sizeof(int));
        arr[0] = 1;
	for (int i=1; i<=n; i++) {
        	int total = 0;
		for (int j = 0; j < steps.size(); j++) {
			if (i - steps[j] >= 0) {
				total += arr[i-steps[j]];
			}
                }
		arr[i] = total;
        }
	return arr[n];

}

int main(int argc, char *argv[]) {
	int n = 15;
	vector<int> steps{ 1,2,3,5 };
	vector<int> step1{ 1 };
	vector<int> step2{ 2 };
	vector<int> step3{ 3 };
	cout << "Number of ways to climb " << n << " stairs in 1 or 2 step jumps using naive method is " << naiveNumWaysToClimb(n) << endl; 
	cout << "Number of ways to climb " << n << " stairs in 1 or 2 step jumps using DP is " << numWaysToClimb(n) << endl; 
	cout << "Number of ways to climb " << n << " stairs in 1 or 2 step jumps using DP with constant space is " << numWaysToClimbEff(n) << endl; 
	cout << "Number of ways to climb " << n << " stairs in 1 step jumps using naive method is " << naiveNumWaysToClimbWithSetOfJumps(n, step1) << endl;
	cout << "Number of ways to climb " << n << " stairs in 1 step jumps using DP is " << numWaysToClimbWithSetOfJumps(n, step1) << endl;
	cout << "Number of ways to climb " << n << " stairs in 2 step jumps using naive method is " << naiveNumWaysToClimbWithSetOfJumps(n, step2) << endl;
	cout << "Number of ways to climb " << n << " stairs in 2 step jumps using DP is " << numWaysToClimbWithSetOfJumps(n, step2) << endl;
	cout << "Number of ways to climb " << n << " stairs in 3 step jumps using naive method is " << naiveNumWaysToClimbWithSetOfJumps(n, step3) << endl;
	cout << "Number of ways to climb " << n << " stairs in 3 step jumps using DP is " << numWaysToClimbWithSetOfJumps(n, step3) << endl;
	cout << "Number of ways to climb " << n << " stairs in 1,2,3,5 step jumps using naive method is " << naiveNumWaysToClimbWithSetOfJumps(n, steps) << endl;
	cout << "Number of ways to climb " << n << " stairs in 1,2,3,5 step jumps using DP is " << numWaysToClimbWithSetOfJumps(n, steps) << endl;
	return 1;
}
