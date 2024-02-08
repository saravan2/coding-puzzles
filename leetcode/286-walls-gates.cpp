class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int wall = -1;
        int gate = 0;
        int emptyRoom = 2147483647;
        vector<pair<int, int>> adjacents = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<pair<int, int>> gates;
        int m = rooms.size();
        int n = rooms[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == gate) {
                    gates.push(make_pair(i, j));
                }
            }
        }
        int distance = 0;
        while (!gates.empty()) {
            int breadth = gates.size();
            distance++;
            while (breadth) {
                auto [x , y] = gates.front();
                gates.pop();
                for (auto const& adjacent : adjacents) {
                    int i = x + adjacent.first;
                    int j = y + adjacent.second;
                    if (i >= 0 && i < m && j >= 0 && j < n && rooms[i][j] == emptyRoom) {
                        rooms[i][j] = distance;
                        gates.push(make_pair(i, j));
                    }
                }
                breadth--;
            }
        }
    }
};