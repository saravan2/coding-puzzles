class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int nr = grid.size();
        int nc = grid[0].size();
        std::vector<std::vector<bool>> visited(nr, std::vector<bool>(nc, false));

        std::deque<pair<int, int>> dq;
        int fresh = 0;
        for (int r = 0; r < nr; r++) {
            for (int c = 0; c < nc; c++) {
                if (grid[r][c] == 2) {
                    dq.push_back({r, c});
                } else if (grid[r][c] == 1) {
                    fresh++;
                }
            }
        }

        if (fresh == 0) {
            return 0;
        }

        if (dq.empty()) {
            return -1;
        }

        int level = 0;

        std::vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        
        while (!dq.empty()) {
            int lsize = dq.size();
            while(lsize--) {
                pair<int, int> rc = dq.front();
                dq.pop_front();
                for (pair<int, int> drc : dirs) {
                    int r = rc.first + drc.first;
                    int c = rc.second + drc.second;
                    if (r >= 0 && r < nr && c >= 0 && c < nc && !visited[r][c] && grid[r][c] == 1) {
                        visited[r][c] = true;
                        fresh--;
                        dq.push_back({r, c});
                    }
                }
            }
            level++;
        }

        if (!fresh) {
            return (level - 1);
        } else {
            return -1;
        }
    }
};