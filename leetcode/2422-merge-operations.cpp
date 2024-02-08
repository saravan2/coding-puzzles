class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int count = 0;
        int i = 0, j = nums.size() - 1;
        vector<long long> nums_copy(nums.begin(), nums.end());
        while (i < j) {
            if (nums_copy[i] == nums_copy[j]) {
                i++;
                j--;
                continue;
            } else if (nums_copy[i] < nums_copy[j]) {
                nums_copy[i+1] += nums_copy[i];
                i++;
                count++;
            } else {
                nums_copy[j-1] += nums_copy[j];
                j--;
                count++;
            }
        }
        return count;
    }
};