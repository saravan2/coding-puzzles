#include<iostream>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
using namespace std;
class solutions {
	private:
		string expr;
		map<string, vector<int> > lookup;
		vector<int> results;
		bool isOperator(char op) {
			if (op == '+' || op == '-' || op == '*') {
				return true;
			}
			return false;
		}
		vector<int> calculateAllScenarios(string input) {
			if (lookup.find(input) != lookup.end()) {
//				cout << "SAR saved ! input was " << input << endl;
				return lookup[input];
			}
//			cout << "SAR : " << input << endl;
			vector<int> result;
			result.clear();
			for (int i=0; i <= input.length(); i++) {
				if (isOperator(input[i])) {
					vector<int> preResult = calculateAllScenarios(input.substr(0, i));
					vector<int> postResult = calculateAllScenarios(input.substr(i+1));
					for (int j=0; j < preResult.size(); j++) {
						for (int k=0; k<postResult.size(); k++) {
							if (input[i] == '+') {
//								cout << "SAR : preSize " << preResult.size() << " postSize " << postResult.size() << " pre expr " << input.substr(0, i) << " " << (j+1) << " value : " << preResult[j] << " " << input[i] << " post expr " << input.substr(i+1) << " " << (k+1) << " value : " << postResult[k] << endl;		
								result.push_back((preResult[j] + postResult[k]));
							} else if (input[i] == '-') {
//								cout << "SAR : preSize " << preResult.size() << " postSize " << postResult.size() << " pre expr " << input.substr(0, i) << " " << (j+1) << " value : " << preResult[j] << " " << input[i] << " post expr " << input.substr(i+1) << " " << (k+1) << " value : " << postResult[k] << endl;		
								result.push_back((preResult[j] - postResult[k]));
							} else if (input[i] == '*') {
//								cout << "SAR : preSize " << preResult.size() << " postSize " << postResult.size() << " pre expr " << input.substr(0, i) << " " << (j+1) << " value : " << preResult[j] << " " << input[i] << " post expr " << input.substr(i+1) << " " << (k+1) << " value : " << postResult[k] << endl;		
								result.push_back((preResult[j] * postResult[k]));
							}
						}
					}
				}	
			}
			if (result.size() == 0) {
				result.push_back(atoi(input.c_str()));
			}
//			cout << "SAR : input " << input << " result size " << result.size() << endl;
			lookup[input] = result;
			return result;

		}
	
	public:
		printSolutions() {
			cout << " All possible solutions for given expression " << expr << " is : ";
			for (int i = 0; i < results.size(); i++) {
				cout << results[i] << " ";
			}
			cout << endl;
		}
	
	solutions(string str) {
		expr = str;
		results = calculateAllScenarios(expr);
	}
			
			
};

int main(int argc, char* argv[]) {
	string expr;
	cout << "Enter an expression without spaces between operands and operators (+, -, *) : ";
	cin >> expr;
	solutions s(expr);
	s.printSolutions();
}
