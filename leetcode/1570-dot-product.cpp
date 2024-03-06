class SparseVector {
private:
    unordered_map<int, int> valueAtIndex;
    
public:
    const unordered_map<int, int>& getValueAtIndex() {
        return valueAtIndex;
    }

    SparseVector(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i]) {
                valueAtIndex[i] = nums[i];
            }
        }
    }
    
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int product = 0;
        const unordered_map<int, int>& secValueAtIndex = vec.getValueAtIndex();
        for (auto &[i, value]: this->valueAtIndex) {
            if (secValueAtIndex.count(i)) {
                product += value * secValueAtIndex.at(i);
            }
        }
        return product;
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);