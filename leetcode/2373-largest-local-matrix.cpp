class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> answer(n-2, vector<int>((n-2), INT_MIN));

        for (int i = 0; i < (n-2); i++) {
            for (int j = 0; j < (n-2); j++) {
                int value = INT_MIN;
                for (int x = i; x < (i+3); x++) {
                    for (int y = j; y < (j+3); y++) {
                        value = max(grid[x][y], value);
                    }
                }
                answer[i][j] = value;
            }
        }
        return answer;
    }
};