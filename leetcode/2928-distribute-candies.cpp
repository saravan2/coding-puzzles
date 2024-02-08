class Solution {
    #define NUM_CHILDREN 3
    long long waysToDistribute(int n, int limit, int children, vector<vector<int>>& dp) {
        if (!n) {
            return 1;
        }

        if (!children) {
            return 0;
        }

        if (dp[n][children] != -1) {
            return dp[n][children];
        }

        int count = 0;

        // skip
        count = waysToDistribute(n, limit, children - 1, dp);

        // pick
        for (int i = 1; i <= min(n, limit); i++) {
            count += waysToDistribute(n - i, limit, children - 1, dp);
        }

        return dp[n][children] = count;
    }
public:
    long long distributeCandies(int n, int limit) {
        vector<vector<int>> dp(n + 1, vector<int>(NUM_CHILDREN + 1, -1));
        return waysToDistribute(n, limit, NUM_CHILDREN, dp);
    }
};