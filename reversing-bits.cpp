#include<iostream>
#include <bitset>
#include<string>
using namespace std;
unsigned int reverseBitsEvery(unsigned int x, int every) {
	unsigned int reversed = 0;
	unsigned int everyBits = 0;
	int numOfBits = sizeof(x) * 8;
	int i,j,k, l;
	for (i = 0, j = 0, k = 0, l = 0; i < numOfBits ; i++) {
		int temp = (x & (1<<i));
		if (j < every) {
			if (temp)
				everyBits |= (1<<j);
			j++;
		} else {
//			cout << "SAR j " << j << " everyBits " << everyBits <<endl;
			for (k = (every - 1); k >= 0; k--, l++) {
				if (everyBits & (1<<k))
					reversed |= (1<<l);
			}
			everyBits = 0;
			j = 0;
			if (temp)
				everyBits |= (1<<j);
			j++;
		}
	}
	// cout << "SAR j " << j << " everyBits " << everyBits << " l " << l << endl;
	for (j = (j-1); j >= 0; j--, l++) {
		if (everyBits & (1<<j))
			reversed |= (1<<l);
	}
		
	return reversed;
}

int main() {
	unsigned int x;
	cout << "Enter integer : "<< endl;
	cin >> x;
//      Bitset method to print bitmap
//	cout<<bitset<32>(x)<<endl;
	cout << "Printing " << x << "'s binary representation : "<<endl; 
	for (unsigned int i = 1 << 31; i > 0; i = i / 2)
        	(x & i)? cout <<"1": cout <<"0";
	cout<<endl;
	string str;
	cout<<"Attempting to reverse 2 bits in this bitmap : "<<endl;
	for (unsigned int i = 1 << 31; i > 0; i = i / 2) {
		str = ((x & i)?"1":"0") + str;
		if (str.size()==2) {
			cout<<str;
			str.clear();
		}
	}
	cout<<endl;
	cout<<"Attempting to reverse every 2 bits inside integer datatype : "<<endl;
	unsigned int reverseX = reverseBitsEvery(x, 2);
	for (unsigned int i = 1 << 31; i > 0; i = i / 2)
        	(reverseX & i)? cout <<"1": cout <<"0";
	return 1;
}
