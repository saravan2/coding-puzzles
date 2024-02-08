class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        bool carry = true;
        deque<int> plusOne;
        for (int i = digits.size() - 1; i >= 0; i--) {
            int digit = digits[i];
            if (carry) {
                digit++;
                if (digit > 9) {
                    carry = true;
                    plusOne.push_front(0);
                } else {
                    carry = false;
                    plusOne.push_front(digit);
                }
            } else {
                plusOne.push_front(digit);
            }
        }
        if (carry) {
            plusOne.push_front(1);
        }
        return vector<int>(plusOne.begin(), plusOne.end());
    }
};