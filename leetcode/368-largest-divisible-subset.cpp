class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();

        if (n < 2) {
            return nums;
        }
        
        std::sort(nums.begin(), nums.end());
        vector<int> subsetLen(n, 1);
        vector<int> subsetPos(n, -1);
        int maxSubsetLen = 0;
        int lastSubsetIndex = -1;
        vector<int> largestSubset;

        for (int index = 1; index < n; index++) {
            for (int prev = 0; prev < index; prev++) {
                if (!(nums[index] % nums[prev]) && (subsetLen[index] < (subsetLen[prev] + 1))) {
                    subsetLen[index] = subsetLen[prev] + 1;
                    subsetPos[index] = prev;
                }
            }
            if (subsetLen[index] > maxSubsetLen) {
                maxSubsetLen = subsetLen[index];
                lastSubsetIndex = index;
            }
        }

        for (int index = lastSubsetIndex; index != -1; index = subsetPos[index]) {
            largestSubset.push_back(nums[index]);
        }

        return largestSubset;
        
    }
};