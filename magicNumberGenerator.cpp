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


/* Increases efficiency tremendously via early detection and forces backtracking */
bool checkMagicSquareSoFar(vector < vector <int> > &sol, int n, int steps) {
	bool diagonal1SumRequired = false;
	bool diagonal2SumRequired = false;
	bool rowSumRequired = false;
	bool colSumRequired = false;
	int magicNumber = (n * ((n*n) + 1))/2;
	int row = steps / n;
	int col = steps % n;
	int diagonal1Sum = 0;
	int diagonal2Sum = 0;
	int rowSum = 0;
	int colSum = 0;
	if ((row == (n-1)) && (col == 0))
		diagonal2SumRequired = true;
	if ((row == (n-1)) && (col == (n-1)))
		diagonal1SumRequired = true;
	if (row == (n-1))
		rowSumRequired = true;
	if (col == (n-1))
		colSumRequired = true;


	if (diagonal1SumRequired || diagonal2SumRequired || colSumRequired || rowSumRequired) { 
		for (int i=0; i < n; i++) {
			if (diagonal1SumRequired) {
				diagonal1Sum += sol[i][i];
			}
			if (diagonal2SumRequired) {
				diagonal2Sum += sol[i][n-1-i];
			}
			if (colSumRequired) {
				colSum+= sol[row][i];
			}
			if (rowSumRequired) {
				rowSum+= sol[i][col];
			}
		}

		if (colSumRequired && colSum != magicNumber) {
			return false;
		}

		if (rowSumRequired && rowSum != magicNumber) {
			return false;
		}

		if (diagonal1SumRequired && diagonal1Sum != magicNumber) {
			return false;
		}

		if (diagonal2SumRequired && diagonal2Sum != magicNumber) {
			return false;
		}
			
	}

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

void generateMagicSquaresUtilFaster(vector < vector <int> > &sol, int steps, int n, bool *used) {
	if (steps == (n*n)) {
		printMagicSquare(sol);
		return;
	}

	for (int i=1; i<=(n*n); i++) {
		if (used[i])
			continue;

		used[i] = true;
		sol[(steps/n)][(steps%n)] = i;
		if (checkMagicSquareSoFar(sol, n, steps)) {
			generateMagicSquaresUtilFaster(sol, (steps+1), n, used);
		}
		used[i] = false;
		sol[(steps/n)][(steps%n)] = 0;
	}
	return;	
}

bool generateMagicSquareUtilFaster(vector < vector <int> > &sol, int steps, int n, bool *used) {
	if (steps == (n*n)) {
		printMagicSquare(sol);
		return true;
	}

	for (int i=1; i<=(n*n); i++) {
		if (used[i])
			continue;

		used[i] = true;
		sol[(steps/n)][(steps%n)] = i;
		if (checkMagicSquareSoFar(sol, n, steps) &&
		    generateMagicSquareUtilFaster(sol, (steps+1), n, used)) {
			return true;
		}
		used[i] = false;
		sol[(steps/n)][(steps%n)] = 0;
	}

	return false;	
}

void generateMagicSquare(int n) {
	if ((n == 2) || (n <= 0)) {
		cout << "No solution possible" << endl;
		return;
	}
	vector < vector <int> > sol(n, vector<int>(n));
	bool* used = new bool[(n*n) + 1];
	generateMagicSquareUtilFaster(sol, 0, n, used);
	delete[] used;
}

void generateMagicSquares(int n) {
	if ((n == 2) || (n <= 0)) {
		cout << "No solution possible" << endl;
		return;
	}
	vector < vector <int> > sol(n, vector<int>(n));
	bool* used = new bool[(n*n) + 1];
//	generateMagicSquaresUtil(sol, 0, n, used);
	generateMagicSquaresUtilFaster(sol, 0, n, used);
	delete[] used;
	
}
 
int main(int argc, char *argv[])
{
	int n;
	char c;
	cout << "Enter magic Square size : " << endl;
	cin >> n;
	cout << "One possible result might be : " << endl;
	generateMagicSquare(n);
	cout << "Do you want to generate all possible magic squares ? (Y/N)" << endl;
	cin >> c;
	if (toupper(c) == 'Y') {
		generateMagicSquares(n);	
	}
	return 0;
}
