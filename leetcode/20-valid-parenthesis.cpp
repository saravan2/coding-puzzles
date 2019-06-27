class Solution {
public:
    bool isValid(string s) {
        unsigned int length = s.length();
        if (length == 0) {
            return true;
        } else if (length & 0x1) {
            return false;
        }
        
        stack<char>soFar;
        for (int i=0; i<length; i++) {
            char cur = s[i];
            if (cur == '(' || cur == '{' || cur == '[') {
                soFar.push(cur);
            } else if (cur == ')') {
                if (soFar.empty() || soFar.top() != '(') {
                    return false;
                }
                soFar.pop();
            } else if (cur == '}') {
                if (soFar.empty() || soFar.top() != '{') {
                    return false;
                }
                soFar.pop();
            } else if (cur == ']') {
                if (soFar.empty() || soFar.top() != '[') {
                    return false;
                }
                soFar.pop();
            }
        }
        
        if (soFar.empty()) {
            return true;
        }
        
        return false;
        
    }
};
