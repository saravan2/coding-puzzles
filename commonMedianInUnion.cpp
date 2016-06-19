#include<iostream>
#include<limits>
#include<cassert>
using namespace std;

// Works with duplicates present in the sorted arrays

int findKthElement(int a[], int b[], int sizeA, int sizeB, int k) {
	// Paranoid assert checks
	assert((k > 0) && (k <= (sizeA + sizeB)));
	assert((sizeA >= 0) && (!(((sizeA > 0) && (a == NULL)) || ((sizeA == 0) && (a != NULL)))));
	assert((sizeB >= 0) && (!(((sizeB > 0) && (a == NULL)) || ((sizeB == 0) && (b != NULL)))));
	assert(!((sizeA == 0) && (sizeB == 0)) || ((a == NULL) && (b == NULL)));

	if (sizeA == 0) {
		return b[k];
	} else if (sizeB == 0) {
		return a[k];
	}

//	i and j can be anything even i = sizeA/2
//	we chose weights of array sizes
//	i+j = k-1 is the invariant maintained
	int i = (int)(((double)sizeA / (sizeA + sizeB)) * (k-1));
	int j = (k-1) - i;

//	a[-1] && b[-1] are -INFINITY and a[sizeA] and b[sizeB] are +INFINITY
//	to maintain invariant
	int ai_1 = ((i == 0) ? numeric_limits<int>::min() : a[i-1]);
	int bj_1 = ((j == 0) ? numeric_limits<int>::min() : b[j-1]);
	int ai = ((i == sizeA) ? numeric_limits<int>::max() : a[i]);
	int bj = ((j == sizeB) ? numeric_limits<int>::max() : b[j]);

	if (bj_1 <= ai && ai <= bj)
		return ai;
	else if (ai_1 <= bj && bj <= ai)
		return bj;

	if (ai <= bj)
		// exclude ai and below portion
		// exclude bj and above portion
		return findKthElement(a+i+1, b, sizeA-i-1, j, k-i-1);
	else
		// exclude ai and above portion
		// exclude bj and below portion
		return findKthElement(a, b+j+1, i, sizeB-j-1, k-j-1);
}

double findCommonMedianInUnion(int a[], int b[], int sizeA, int sizeB) {
	// Paranoid assert checks
	assert((sizeA >= 0) && (!(((sizeA > 0) && (a == NULL)) || ((sizeA == 0) && (a != NULL)))));
	assert((sizeB >= 0) && (!(((sizeB > 0) && (a == NULL)) || ((sizeB == 0) && (b != NULL)))));
	assert(!((sizeA == 0) && (sizeB == 0)) || ((a == NULL) && (b == NULL)));
	int ul = sizeA + sizeB;

	// When the union length is odd, the median is position : ul/2 + 1 , summarized by (ul + 1) >> 1
	if (ul & 1)
		return findKthElement(a, b, sizeA, sizeB, ((ul + 1) >> 1));
	else
	// When the union length is even, the median is calculated using average of values at ul/2 and (ul/2 + 1)
		return (
			(findKthElement(a, b, sizeA, sizeB, ((ul + 1) >> 1)) + 
			findKthElement(a, b, sizeA, sizeB, ((ul + 2) >> 1))) 
			/
			2.0);
}

int main(int argc, char *argv[]) {
	int a[] = { 1, 1, 5};
	int b[] = { 4, 5 };
//	std::cout << "kth element is " << findKthElement(a, b, sizeof(a)/sizeof(int), sizeof(b)/sizeof(int), 1);
	std::cout << "Common median is " << findCommonMedianInUnion(a, b, sizeof(a)/sizeof(int), sizeof(b)/sizeof(int)) << endl;
	int c[] = { 1, 2, 4, 8, 9, 10 };
	int d[] = { 3, 5, 6, 7 };
	std::cout << "Common median is " << findCommonMedianInUnion(c, d, sizeof(c)/sizeof(int), sizeof(d)/sizeof(int)) << endl;
	
}
