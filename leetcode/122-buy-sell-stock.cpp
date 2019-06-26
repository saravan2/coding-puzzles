class Solution {
public:
    int maxProfit(vector<int>& prices) {
        unsigned int size = prices.size();
        if (size == 0 || size == 1)
            return 0;
        int valley = 0;
        int peak = 0;
        unsigned int i = 0;
        int soFarProfit = prices[peak] - prices [valley];
        for (int i = 1; i < size; i++) {
            if (prices[i] < prices[valley]) {
                valley = i;
                peak = i;
            } else {
                peak = i;
                soFarProfit += (prices[peak] - prices[valley]);
                valley = i;
            }
        }
        return soFarProfit;
    }
};
