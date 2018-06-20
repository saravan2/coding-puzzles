/* Decides whether input string conforms to regex with special characters
 * : *,+
 * * - Any sequence of characters or empty string
 * + - Any character or empty string
 */
// Credits : Careercup
#include<iostream>
using namespace std;
bool _isMatch(string::iterator ss, string::iterator sn, string::iterator rs, string::iterator rn) {
	if (ss == sn && rs == rn) 
		return true;

	if (ss == sn) {
		if (*rs == '+' || *rs == '*') {
			_isMatch(ss, sn, ++rs, rn);
		} else {
			return false;
		}
	}

	if (*rs == '+') {
		_isMatch(++ss, sn, rs++, rn);
	}

	if (*rs == '*') {
		rs++;
		bool result = false;
		while (ss != sn) {
			result |= _isMatch(++ss, sn, rs, rn);
		}
		return result;
	}

	if (*ss == *rs) {
		return _isMatch(++ss, sn, ++rs, rn);
	} else {

		return false;
	}
}
bool isMatch(string str, string regex) {
	return _isMatch(str.begin(), str.end(), regex.begin(), regex.end());
}

int main(int argc, char* argv[]) {
	cout <<"aaabbbc " << string(isMatch("aaabbbc","a*")? "matches ":"does not match ") << "regex a*\n";
	cout <<"baaabab " << string(isMatch("baaabab","ba*a++")? "matches ":"does not match ") << "regex ba*a++\n";
//	isMatch("aaabbbc","a*")?cout<<"aaabbbc matches regex a*\n":cout<<"aaabbbc does not match regex a*\n";
	return 1;
}
