class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int count = 0;
        if (grid.empty()) {
            return count;
        }
        for (auto const & row : grid) {
            for (auto const & col : row) {
                if (col < 0) {
                    count++;
                }
            }
        }
        return count;
    }
};