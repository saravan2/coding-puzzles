class Solution {
public:
    long long countOperationsToEmptyArray(vector<int>& nums) {
        unordered_map<long long, int> num_pos;
        int n = nums.size();
        long long count  = n;
        for (int i = 0; i < n; i++) {
            num_pos[nums[i]] = i;
        }
        sort(nums.begin(), nums.end(), [&](int a, int b) {
            return a < b;
        });
        for (int i = 1; i < n; i++) {
            if (num_pos[nums[i]] < num_pos[nums[i-1]]) {
                count += n - i;
            }
        }
        return count;
    }
};