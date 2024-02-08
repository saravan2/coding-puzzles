class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        vector<int> targets;
        sort(nums.begin(), nums.end(), [&](auto const& a, auto const& b) {
            return a < b;
        });
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > target)
                break;
            if (nums[i] == target) {
                targets.push_back(i);
            }
        }
        return targets;
    }
};