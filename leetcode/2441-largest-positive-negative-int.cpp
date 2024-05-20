class Solution {
public:
    int findMaxK(vector<int>& nums) {
        int k = -1;
        unordered_set<int> seen;

        for (const auto& num : nums) {
            const auto abs_num = std::abs(num);

            if (abs_num > k && seen.contains(-num)) {
                k = abs_num;
            }
            seen.insert(num);
        }

        return k;
    }
};