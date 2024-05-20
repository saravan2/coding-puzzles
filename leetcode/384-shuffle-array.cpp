class Solution {
private:
    vector<int> original;
    vector<int> current;
public:
    Solution(vector<int>& nums) {
        original = nums;
        current = nums;
    }
    
    vector<int> reset() {
        return original;
    }
    
    vector<int> shuffle() {
        if (current.size() > 1) {
            size_t n = current.size();
            for (unsigned int i = 0; i < n; i++) {
                unsigned int offset = (std::rand() % n);
                iter_swap(current.begin()+i, current.begin()+offset);
            }
        }
        return current;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */