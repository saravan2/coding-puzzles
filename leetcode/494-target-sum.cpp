class Solution {
    int solve(vector<int>& nums, int target, map<pair<int, int>, int> &dp, int index, int value) {
        if (index == nums.size()) {
            if (target == value) {
                return 1;
            }
            return 0;
        }
        if (dp.count({index, value})) {
            return dp[{index, value}];
        }
        int positive = solve(nums, target, dp, index+1, value + nums[index]);
        int negative = solve(nums, target, dp, index+1, value - nums[index]);
        return dp[{index, value}] = positive + negative;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        map<pair<int, int>, int> dp;
        return solve(nums, target, dp, 0, 0);
    }
};