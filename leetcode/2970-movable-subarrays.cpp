class Solution {
public:
    int incremovableSubarrayCount(vector<int>& nums) {
        int count = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i; j < nums.size(); j++) {
                bool canBeRemoved = true;
                int lastValue = -1;

                for (int k_i = 0; k_i < i; k_i++) {
                    if (lastValue >= nums[k_i]) {
                        canBeRemoved = false;
                        break;
                    }
                    lastValue = nums[k_i];
                }

                for (int k_j = j + 1; k_j < nums.size(); k_j++) {
                    if (lastValue >= nums[k_j]) {
                        canBeRemoved = false;
                        break;
                    }
                    lastValue = nums[k_j];
                }

                if (canBeRemoved) {
                    count++;
                }
            }
        }

        return count;
    }
};
