class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        //std::unordered_map<int, int> diagonals;
        for (int r = 0; r < matrix.size(); r++) {
            for (int c = 0; c < matrix[0].size(); c++) {
                //if (!diagonals.count(r - c)) {
                //    diagonals[r - c] = matrix[r][c];
                //} else {
                //    if (diagonals[r - c] != matrix[r][c]) {
                //        return false;
                //    }
                //}
                if ( r > 0 && c > 0 && matrix[r-1][c-1] != matrix[r][c]) {
                    return false;
                }
            }
        }
        return true;
    }
};