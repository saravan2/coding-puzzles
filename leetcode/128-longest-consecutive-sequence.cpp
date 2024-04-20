class UnionFindBySize {
private:
    vector<int> parent;
    vector<int> size;
public:
    UnionFindBySize(int n) : size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
        }
    }

    int largestbysize() {
        vector<int>:: iterator it = std::max_element(size.begin(), size.end());
        if (it == size.end()) {
            return 0;
        } else {
            return *it;
        }
    }

    int find(int node) {
        if (node != parent[node]) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    void connect(int source, int destination) {
        int source_parent = find(source);
        int dest_parent = find(destination);

        if (source_parent != dest_parent) {
            if (size[source_parent] < size[dest_parent]) {
                parent[source_parent] = dest_parent;
                size[dest_parent] += size[source_parent];
            } else {
                parent[dest_parent] = source_parent;
                size[source_parent] += size[dest_parent];
            }
        } 
    }
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return n;
        }
        std::map<int, int> elemToIndex;
        UnionFindBySize ufs(n);
        for (int i = 0; i < n; i++) {
            elemToIndex[nums[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            if (elemToIndex.count(nums[i]+1)) {
                ufs.connect(elemToIndex[nums[i]], elemToIndex[(nums[i]+1)]);
            }
            if (elemToIndex.count(nums[i]-1)) {
                ufs.connect(elemToIndex[nums[i]], elemToIndex[(nums[i]-1)]);
            }
        }
        return ufs.largestbysize();
    }
};