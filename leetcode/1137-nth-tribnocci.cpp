class Solution {
public:
    int tribonacci(int n) {
        if (n < 3) {
            return n > 0 ? 1 : 0;
        }
        int t0 = 0, t3 = 0;
        int t1 = 1, t2 = 1;
        for (int i = 0; i < (n-2); i++) {
            t3 = t0 + t1 + t2;
            t0 = t1;
            t1 = t2;
            t2 = t3;
        }
        return t3;
    }
};