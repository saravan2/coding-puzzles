class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
         vector<int> dp(nums.size());
         deque<int> indexesToConsider;
         int sum = nums[0];
         dp[0] = nums[0];
         indexesToConsider.push_back(0);
         for (int i = 1; i < nums.size(); i++) {
             dp[i] = max(0, dp[indexesToConsider.front()]) + nums[i];
             sum = max(sum, dp[i]);
             while(!indexesToConsider.empty() && dp[indexesToConsider.back()] <= dp[i]) {
                 indexesToConsider.pop_back();    
             }
             indexesToConsider.push_back(i);
             if (indexesToConsider.front() == (i - k))
                indexesToConsider.pop_front();
         }
         return sum;
    }
};