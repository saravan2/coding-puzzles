// Union Find by Rank + Path Compression
class UnionFindByRank {
private:
    std::vector<int> parent;
    std::vector<int> rank;
public:
    UnionFindByRank(int n) : rank(n, 1) {
        for (int node = 0; node < n; node++) {
            parent.push_back(node);
        }
    }

    int find(int node) {
        if (node != parent[node]) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    void connect(int source, int destination) {
        int parent_source = find(source);
        int parent_destination = find(destination);
        if (parent_source != parent_destination) {
            if (rank[parent_source] > rank[parent_destination]) {
                parent[parent_destination] = parent_source;
            } else if (rank[parent_source] < rank[parent_destination]) {
                parent[parent_source] = parent_destination;
            } else {
                parent[parent_source] = parent_destination;
                rank[parent_destination] += 1;
            }
        }
    }
};

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if ((n <= 0) || (source > n) || (destination > n)) {
            return false;
        } else if (n == 1) {
            return true;
        }

        UnionFindByRank ufr(n);
        for (auto& edge : edges) {
            ufr.connect(edge[0], edge[1]);
        }

        return ufr.find(source) == ufr.find(destination);
    }
};