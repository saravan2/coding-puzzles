class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        unordered_set<int> sofar;
        vector<int> missing;
        for (int i = 0; i < nums.size(); i++) {
            sofar.insert(nums[i]);
        }
        for (int i=0; i < nums.size(); i++) {
            if (sofar.find(i+1) == sofar.end()) {
                missing.push_back(i+1);
            }
        }
        return missing;
    }
};
