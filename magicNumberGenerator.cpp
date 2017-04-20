/* C++ program to generate all possible MagicSquare solutions using backtracking */
#include<iostream>
#include<vector>
using namespace std;

void printMagicSquare(vector < vector <int> > &sol) {
		cout << "Found a Solution !" << endl;
		for (vector< vector<int> >::iterator row=sol.begin(); row != sol.end(); row++) {
			for (vector<int>::iterator col=row->begin(); col != row->end(); col++) {
				cout << *col << " ";
			}
			cout <<endl;
		}	
		cout <<endl;
}

bool checkMagicSquare(vector < vector <int> > &sol, int n) {
	int magicNumber = (n * ((n*n) + 1))/2;
	int diagonal1Sum = 0;
	int diagonal2Sum = 0;
	for (int i=0; i < n; i++) {
		int rowSum = 0;
		int colSum = 0;
		diagonal1Sum += sol[i][i];
		diagonal2Sum += sol[i][n-1-i];
		for (int j=0; j < n; j++) {
			rowSum+= sol[i][j];
			colSum+= sol[j][i];
		}
		if ((rowSum != magicNumber) || (colSum != magicNumber))
			return false;
	}

	if ((diagonal1Sum != magicNumber) || (diagonal2Sum != magicNumber))
		return false;

	return true;
		

}

/* Brute force insight, there are n*n cells to fill. Lets step through every assignment
and backtrack the used and assigned values to find all possible solutions */	
void generateMagicSquaresUtil(vector < vector <int> > &sol, int steps, int n, bool *used) {
	if (steps == (n*n)) {
		if (checkMagicSquare(sol, n)) {
			printMagicSquare(sol);
		}
		return;
	}

	for (int i=1; i<=(n*n); i++) {
		if (used[i])
			continue;

		used[i] = true;
		sol[(steps/n)][(steps%n)] = i;
		generateMagicSquaresUtil(sol, (steps+1), n, used);
		used[i] = false;
		sol[(steps/n)][(steps%n)] = 0;
	}
	return;	
}

void generateMagicSquare(int n) {
	if ((n == 2) || (n <= 0)) {
		cout << "No solution possible" << endl;
		return;
	}
	vector < vector <int> > sol(n, vector<int>(n));
	bool used[(n*n) + 1] = {false};
	generateMagicSquaresUtil(sol, 0, n, used);
}
 
int main(int argc, char *argv[])
{
	int n;
	cout << "Enter magic Square size : " << endl;
	cin >> n;
	generateMagicSquare(n);	
	return 0;
}
