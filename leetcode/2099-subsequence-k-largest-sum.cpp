class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        int n = nums.size();
        if ((n < 1) || (k < 0)) {
            return vector<int>();
        }
        if (k >= n) {
            return nums;
        }
        vector<int> subsequence;
        for (int i = 0; i < k; i++) {
            subsequence.push_back(nums[i]);
        }
        for (int i = k; i < n; i++) {
            int min_element_index = std::min_element(subsequence.begin(), subsequence.end()) - subsequence.begin();
            if (subsequence[min_element_index] < nums[i]) {
                subsequence.erase(subsequence.begin() + min_element_index);
                subsequence.push_back(nums[i]);
            }
        }
        return subsequence;
    }
};