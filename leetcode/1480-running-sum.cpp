class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        if (nums.empty()) {
            return vector<int>();
        }
        vector<int> rsum(nums.size());
        int sum = 0, index = 0;
        for (auto const & num : nums) {
            sum += num;
            rsum[index] = sum;
            index++;
        }
        return rsum;
    }
};