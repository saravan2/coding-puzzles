class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        int mod = 1e9 + 7;
        // dp[n][sum];
        vector<vector<long long>> dp(n+1, vector<long long>((target + 1), 0));
        dp[0][0] = 1ll;

        for (int dice = 1; dice <= n; dice++) {
            for (int sum = 1; sum <= target; sum++) {
                for (int face = 1; face <= min(sum, k); face++) {
                    int previousSum = sum - face;
                    dp[dice][sum] = ((dp[dice][sum] % mod) + (dp[dice - 1][previousSum] % mod)) % mod;
                }
            }
        }
        return dp[n][target];
    }
};