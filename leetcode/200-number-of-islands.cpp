class Solution {
public:
    int dfs (vector<vector<char>>&grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size()) {
            return 0;
        }
        
        if (grid [i][j] == '0') {
            return 0;
        }
        grid [i][j] = '0';
        dfs (grid, i-1, j);
        dfs (grid, i+1, j);
        dfs (grid, i, j-1);
        dfs (grid, i, j+1);
        
        return 1;
    }
    int numIslands (vector<vector<char>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        
        int numIslands = 0;
        
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid [i][j] == '1') {
                    numIslands += dfs (grid, i, j);
                }
            }
        }
        
        return numIslands;
    }
};
