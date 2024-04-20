#include <iostream>

class DisjointSet {
private:
    int n;
    int* parent;
    int* rank;

public:
    DisjointSet(int n) {
        this->n = n;
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return;
        }
        if (rank[u] > rank[v]) {
            parent[v] = u;
        } else if (rank[u] < rank[v]) {
            parent[u] = v;
        } else {
            parent[u] = v;
            rank[v]++;
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }
};

int main(int argc, char const *argv[]) {
    DisjointSet ds(5);
    ds.merge(0, 2);
    ds.merge(4, 2);
    ds.merge(3, 1);
    for (int i = 0; i < 5; i++) {
        std::cout << "Finding parent of " << i << ": " << ds.find(i) << std::endl;
    }
    return 0;
}