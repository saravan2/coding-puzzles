#include<iostream>
#include<algorithm>
using namespace std;

// Notes : We can use push_back() method in string class
// to append a char digit (int + '0') to the end of the string
// num2 will always be bigger number in terms of length 
// We use algorithm header file methods like swap and reverse
// When adding we have to add individual char digits from end of 
// string number. Because of difference in size of numbers being added
// we need to calculate the relative offset to reach end of number for
// both num1 and num2. When the smaller number is processed, we continue
// with the larger number and carry to produce the sum.

string largeSum(string num1, string num2) {
	if (num1.length() > num2.length())
		swap(num1, num2);

	int n1 = num1.length();
	int n2 = num2.length();
	int carry = 0;
	int diff = (n2 - n1);
	string result = "";

	for (int i = n1 - 1; i >=0; i--) {
		int sum = ((num1[i] - '0') +
				(num2[i + diff] - '0') +
				carry);
		result.push_back((sum % 10) + '0');
		carry = sum / 10;
	}

	for (int i = diff - 1; i >=0; i--) {
		int sum = ((num2[i] - '0') +
				carry);
		result.push_back((sum % 10) + '0');
		carry = sum / 10;
	}

	if (carry) 
		result.push_back(carry + '0');
	reverse(result.begin(), result.end());
	return result;


}

int main() {
	string num1 = "123";
	string num2 = "1999934";
	cout << "Sum of " << num1 << " + " << num2 << " is " << largeSum(num1, num2) << endl;
	return 1;

}
