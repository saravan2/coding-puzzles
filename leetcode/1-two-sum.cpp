class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        map<int, int> hashMap;
        
        for (int i=0; i < nums.size(); i++) {
            if (hashMap.find(nums[i])!=hashMap.end()) {
                result.push_back(hashMap[nums[i]] + 1);
                result.push_back(i + 1);
                return result;
            } else {
                hashMap[target-nums[i]] = i;
            }
        }
        return result;
    }
};
