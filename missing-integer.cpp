/* Header files */
#include<iostream>
#include<math.h>

/* Globals */
const int n = 10;
const int m = floor(log2(n))+1;

/* Integer sequence is stored in binary form with access to every bit
   taking const time */
int A[m][n] = {
	{0,0,1,0,0,0,0,1,1,0},
	{0,0,0,1,1,1,0,0,0,0},
	{1,0,1,1,0,0,0,0,0,1},
	{1,1,0,1,0,1,0,1,0,0}
	
};

/* O(n) algorithm to find the missing integer in this sequence */ 
int main() {
	int i, j, t, n0, n1, ntemp = n;
	int B[n], res[m];

	/*  Initializing res, B arrays */
	for (i = 0; i < m; i++)
		res[i] = -1;

	for (i = 0; i < n; i++)
		B[i]=i;

	for (i = (m-1); i >= 0; i--) {
		n0 = n1 = 0;

		for (j = 0; j < ntemp; j++) {
			if (A[i][B[j]] == 0)
				n0++;
			else
				n1++;
		}

		if ((n0 - n1 == 2) || (n0 - n1 == 1)) 
			res[i] = 1;
		else if ((n0 - n1 == 0) || (n0 - n1 == -1)) 
			res[i] = 0;
		else
			std::cout<<"Warning"<<std::endl;

		for (j=0, t=0; j<ntemp; j++) {
			if (res[i] == A[i][B[j]]) {
				B[t] = B[j];
				t++;
			}
		}

		if (t)
			ntemp = t;
		else if (ntemp % 2 == 0)
			ntemp = (ntemp / 2);
		else 
			ntemp = floor(ntemp/2.0);
	}

	for (i = 0; i < m; i++)
		std::cout << res[i];
	std::cout<<std::endl;
		
	return 0;
}
