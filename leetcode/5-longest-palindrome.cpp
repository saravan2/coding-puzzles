class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) {
            return "";
        }
        
        // Palindromes of size 1 and 2
        // Previous row will have true set at start of palindrome
        vector<vector<bool>> dp(s.length(), vector<bool>(s.length(), false));
        for (int i = 0; i < s.length(); i++) {
            dp[i][i] = true;
            if (i != 0) {
                if (s[i] == s[i-1]) {
                    dp[i][i-1] = true;
                }
            }
        }
        
        // Palindromes of size > 2, built using previous dp result
        // i-1, j+1 will let us know whether there exists a complete
        // palindrome starting from the subsequent character at j+1
        // by checking our previous row in dp
        for (int i = 0; i < s.length(); i++) {
            for (int j = 0; ((i-j+1) > 2); j++) {
                if (s[i] == s[j] && dp[i-1][j+1]) {
                    dp[i][j] = true;
                }
            }
        }
    
        int longestPalindrome = 0;
        string result = "";
        for (int i = s.length()-1; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                if (dp[i][j]) {
                    if ((i-j+1) > longestPalindrome) {
                        result = s.substr(j, i-j+1);
                        longestPalindrome = i-j+1;
                    }
                }
            }
        }
        return result;
    }
};