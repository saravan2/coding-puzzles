class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t reverse = 0;
        for (int i = 0; i < 32; i++) {
            reverse = reverse << 1;
            reverse = reverse | (n & 1);
            n = n >> 1;
        }
        return reverse;
    }
};