class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        int evens = 0;
        for (auto num: nums) {
            if (!(num & 0x1)) {
                evens++;
            }
        }
        return evens >= 2;
    }
};
