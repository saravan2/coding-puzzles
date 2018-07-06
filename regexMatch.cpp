/* Decides whether input string conforms to regex with special characters
 * : *,+
 * * - Any sequence of characters or empty string
 * + - Any character or empty string
 */
// Credits : Careercup
#include<iostream>
using namespace std;
bool _isMatch(string  &ss, unsigned int spos, string &rs, unsigned int rpos) {
	if (spos == ss.length() && rpos == rs.length()) 
		return true;

	if (spos == ss.length() && rpos != rs.length()) {
		if (rs[rpos] == '+' || rs[rpos] == '*') {
			return _isMatch(ss, spos, rs, ++rpos);
		} else {
			return false;
		}
	}

	if (spos != ss.length() && rpos == rs.length()) {
		return false;
	}

	if (rs[rpos] == '+') {
		return _isMatch(ss, ++spos, rs, ++rpos);
	}

	if (rs[rpos] == '*') {
		rpos++;
		bool result = false;
		while (spos!= ss.length()) {
			result |= _isMatch(ss, ++spos, rs, rpos);
			if (result) {
				break;
			}	
		}
		return result;
	}

	if (ss[spos] == rs[rpos]) {
		return _isMatch(ss, ++spos, rs, ++rpos);
	} else {

		return false;
	}
}
bool isMatch(string str, string regex) {
	unsigned int spos = 0;
	unsigned int rpos = 0;
	if (!str.length() && !regex.length()) {
		return true;
	} else {
		return _isMatch(str, spos, regex, rpos);
	}
}

int main(int argc, char* argv[]) {
	cout <<"aaabbbc " << string(isMatch("aaabbbc","a*")? "matches ":"does not match ") << "regex a*\n";
	cout <<"baaabab " << string(isMatch("baaabab","ba*a++")? "matches ":"does not match ") << "regex ba*a++\n";
	return 1;
}
