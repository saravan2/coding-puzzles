class Solution {
public:
    int numWays(int n, int k) {
        if (n == 1) {
            return k;
        } else if (n == 2) {
            return k * k;
        }
        vector<long long> dp(n, 0);
        dp[0] = k;
        dp[1] = k*k;
        for (int i = 2; i < n; i++) {
            dp[i] = (k-1)*(dp[i-1] + dp[i-2]);
        }
        return dp[n-1];
    }
};