class Solution {
    vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    bool canTraverse(int row, int col, vector<vector<int>>& maze) {
        int m = maze.size();
        int n = maze[0].size();
        if (row >= 0 && row < m && col >= 0 && col < n && !maze[row][col]) {
            return true;
        }
        return false;
    }

    bool dfs(vector<vector<int>>& maze, vector<int>& current, vector<int>& destination, vector<vector<bool>>& visited) {
        if (!canTraverse(current[0], current[1], maze) || visited[current[0]][current[1]]) {
            return false;
        }
        if (current == destination) {
            return true;
        }
        visited[current[0]][current[1]] = true;
        for (auto const& [dx, dy]: moves) {
            int row = current[0] + dx;
            int col = current[1] + dy;
            while(canTraverse(row, col, maze)) {
                row += dx;
                col += dy;
            }
            row -= dx;
            col -= dy;
            vector<int> current {row, col};
            if (dfs(maze, current, destination, visited)) {
                return true;
            }
        }
        return false;
    }

    bool bfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination, vector<vector<bool>>& visited) {
        queue<vector<int>> q;
        q.emplace(start);
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            if (current == destination) {
                return true;
            }
            visited[current[0]][current[1]] = true;
            for (auto const& [dx, dy]: moves) {
                int row = current[0] + dx;
                int col = current[1] + dy;
                while(canTraverse(row, col, maze)) {
                    row += dx;
                    col += dy;
                }
                row -= dx;
                col -= dy;
                if (!visited[row][col]) {
                    q.emplace(vector<int>{row, col});
                }
            }
        }
        return false;
    }

public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
        return bfs(maze, start, destination, visited);
    }
};