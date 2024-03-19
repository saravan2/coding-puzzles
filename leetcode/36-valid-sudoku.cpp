class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        const int dimension = 9;
        bool row[dimension][dimension] = {false};
        bool col[dimension][dimension] = {false};
        bool subgrid[dimension][dimension] = {false};

        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int number = board[i][j] - '0' - 1;
                int k = (i / 3) * 3 + (j / 3);
                if (row[i][number] || col[j][number] || subgrid[k][number]) {
                    return false;
                }

                row[i][number] = true;
                col[j][number] = true;
                subgrid[k][number] = true;
            }
        }
        return true;
    }
};