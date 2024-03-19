class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int ways = 0;
        int suffixOddSum = 0;
        int suffixEvenSum = 0;
        int prefixEvenSum = 0;
        int prefixOddSum = 0;
        int n = nums.size();
        vector<int> suffixOdd(n+1, 0);
        vector<int> suffixEven(n+1, 0);
        for (int i = (n -1); i >= 0; i--) {
            if (i & 1) {
                suffixOddSum += nums[i];
            } else {
                suffixEvenSum += nums[i];
            }
            suffixOdd[i] = suffixOddSum;
            suffixEven[i] = suffixEvenSum;
        }

        for (int i = 0; i < n; i++) {
            if (i & 1) {
                if (prefixOddSum + suffixEven[i+1] == prefixEvenSum + suffixOdd[i+1]) {
                    ways++;
                }
                prefixOddSum += nums[i];
            } else {
                if (prefixEvenSum + suffixOdd[i+1] == prefixOddSum + suffixEven[i+1]) {
                    ways++;
                }
                prefixEvenSum += nums[i];
            }
        }
        return ways;
    }
};