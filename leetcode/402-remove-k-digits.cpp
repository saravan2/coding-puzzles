class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> stck;
        for (auto const& digit : num) {
            while (!stck.empty() && k > 0 && stck.top() > digit) {
                stck.pop();
                k--;
            }
            stck.push(digit);
        }
        while(!stck.empty() && k > 0) {
            stck.pop();
            k--;
        }
        string minimum = "";
        while (!stck.empty()) {
            minimum += stck.top();
            stck.pop();
        }
        reverse(minimum.begin(), minimum.end());
        while(minimum.size() && minimum[0] == '0') {
            minimum.erase(minimum.begin());
        }
        if (minimum.empty()) {
            return "0";
        }
        return minimum;
    }
};