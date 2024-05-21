class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();

        if (!n) {
            return n;
        } else if (n == 1) {
            if (s[0] == '0') {
                return 0;
             }
            return n;
        } else if (s[0] == '0') {
            return 0;
        }

        // n >= 2
        std::vector<int> maxDecodingsAtIndex(n, 0);

        // At index 0 we know we have a valid number.
        maxDecodingsAtIndex[0] = 1;

        // Filling up index 1.
        if (s[1] != '0') {
            maxDecodingsAtIndex[1] = maxDecodingsAtIndex[0];
        }
        int two_digit = std::stoi(s.substr(0, 2));
        if (two_digit >= 10 && two_digit <= 26) {
            maxDecodingsAtIndex[1] += 1;
        }

        // The rest
        for (int i = 2; i < n; i++) {
            if (s[i] != '0') {
                maxDecodingsAtIndex[i] = maxDecodingsAtIndex[i-1];
            } 

            int two_digit = std::stoi(s.substr(i - 1, 2));
            if (two_digit >= 10 && two_digit <= 26) {
                maxDecodingsAtIndex[i] += maxDecodingsAtIndex[i-2];
            }
        }

        return maxDecodingsAtIndex[n-1];
    }
};