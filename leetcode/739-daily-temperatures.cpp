class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        unsigned int size = T.size();
        vector<int> result(size, 0);
        stack<int> hotT;
        int max = -1;
        for (int i = size-1; i >=0; i--) {
            while (!hotT.empty() && T[hotT.top()] <= T[i]) {
                hotT.pop();
            }
            if (hotT.empty()) {
                result[i] = 0;
            } else {
                result[i] = hotT.top() - i;
            }
            hotT.push(i);
        }
        return result;
    }
};
