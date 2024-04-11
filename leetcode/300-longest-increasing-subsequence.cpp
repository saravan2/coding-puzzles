class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        
        if (n < 2) {
            return n;
        }
        
        int maxLength = 0;
        std::vector<int> subseqLength(n, 1);


base class derived element