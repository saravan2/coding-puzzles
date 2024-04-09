class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        
        if (n < 2) {
            return n;
        }
        
        int maxLength = 0;
        std::vector<int> subseqLength(n, 1);


        for (int index = 1; index < n; index++) {
            for (int prev = 0; prev < index; prev++) {
                if ((nums[index] > nums[prev]) && (subseqLength[index] < (subseqLength[prev] + 1))) {
                    subseqLength[index] = subseqLength[prev] + 1;
                }
            }
            if (subseqLength[index] > maxLength) {
                maxLength = subseqLength[index];
            }
        }

        return maxLength;
    }
};