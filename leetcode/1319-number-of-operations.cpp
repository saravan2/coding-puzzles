class Solution {
private:
    void dfs(int node, vector<vector<int>>& connected, vector<bool>& visited) {
        visited[node] = true;
        for (auto & neighbor : connected[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, connected, visited);
            }
        }
    }
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        
        if (connections.size() < (n - 1)) {
            return -1;
        }

        vector<vector<int>> connected(n);
        for (auto& connection : connections) {
            connected[connection[0]].push_back(connection[1]);
            connected[connection[1]].push_back(connection[0]);
        }

        vector<bool> visited(n);
        int connectedComponents = 0;

        for(int node = 0; node < n; node++) {
            if (!visited[node]) {
                connectedComponents++;
                dfs(node, connected, visited);
            }
        }

        return (connectedComponents - 1);
    }
};