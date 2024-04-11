class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();

        if (n < 2) {
            return n;
        }

        vector<pair<int, int>> subseqLenCount(n, {1,1});
        int longestSubseq = 1;
        int count = 1;

        for (int index = 1; index < n; index++) {
            for (int prev = 0; prev < index; prev++) {
                if (nums[prev] < nums[index]) {
                    if (subseqLenCount[index].first == (subseqLenCount[prev].first + 1)) {
                        subseqLenCount[index].second += subseqLenCount[prev].second;
                    } else if (subseqLenCount[index].first < (subseqLenCount[prev].first + 1)) {
                        subseqLenCount[index].second = subseqLenCount[prev].second;
                        subseqLenCount[index].first = subseqLenCount[prev].first + 1;
                    }
                }
            }

            if (subseqLenCount[index].first == longestSubseq) {
                count += subseqLenCount[index].second;
            } else if (subseqLenCount[index].first > longestSubseq) {
                longestSubseq = subseqLenCount[index].first;
                count = subseqLenCount[index].second;
            }
        }
        return count;
    }
};