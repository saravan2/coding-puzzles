class Solution {
private:
    int bfs(std::vector<std::vector<int>>& grid, int r, int c, int totalHouses) {
        int nr = grid.size();
        int nc = grid[0].size();
        std::vector<std::vector<int>> neighborsAt {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int distance = 0, houses = 0;

        std::queue<pair<int, int>> q;
        q.push({r, c});

        std::vector<std::vector<bool>> visited(nr, std::vector<bool>(nc, false));
        visited[r][c] = true;
        int steps = 0;
        while (!q.empty() && houses != totalHouses) {
            int end = q.size();
            for (int i = 0; i < end; i++) {
                pair<int, int> curr = q.front();
                q.pop();
                r = curr.first;
                c = curr.second;

                if (grid[r][c] == 1) {
                    distance += steps;
                    houses++;
                    continue;
                }
                for (auto& at : neighborsAt) {
                    int nextr = r + at[0];
                    int nextc = c + at[1];

                    if (nextr >=0 && nextc >= 0 &&\
                        nextr < nr && nextc < nc) {
                        if (!visited[nextr][nextc] && grid[nextr][nextc] != 2) {
                            visited[nextr][nextc] = true;
                            q.push({nextr, nextc});
                        }
                    }
                }
            }
            steps++;
        }

        if (houses != totalHouses) {
            for (r = 0; r < nr; r++) {
                for (c = 0; c < nc; c++) {
                    if (grid[r][c] == 0 && visited[r][c]) {
                        grid[r][c] = 2;
                    }
                }
            }
            return INT_MAX;
        }

        return distance;
    }
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int shortestDistance = INT_MAX;
        int nr = grid.size();
        int nc = grid[0].size();
        int totalHouses = 0;

        for (int r = 0; r < nr; r++) {
            for (int c = 0; c < nc; c++) {
                if (grid[r][c] == 1) {
                    totalHouses++;
                }
            }
        }

        for (int r = 0; r < nr; r++) {
            for (int c = 0; c < nc; c++) {
                if (grid[r][c] == 0) {
                    shortestDistance = std::min(shortestDistance, bfs(grid, r, c, totalHouses));
                }
            }
        }

        return (shortestDistance == INT_MAX) ? -1 : shortestDistance;
    }
};