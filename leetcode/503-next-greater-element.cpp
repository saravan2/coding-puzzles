class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> stck;
        vector<int> nextGreater(n, -1);

        for (int i = ((2 * n) - 1); i >=0; i--) {
            while (!stck.empty() && stck.top() <= nums[i%n]) {
                stck.pop();
            }
            if (i < n) {
                if (!stck.empty()) {
                    nextGreater[i] = stck.top();
                }
            }
            stck.push(nums[i%n]);
        }
        return nextGreater;
    }
};