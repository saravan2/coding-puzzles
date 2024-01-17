#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(int node, int start, int end, const vector<int>& arr) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid, arr);
            build(2 * node + 1, mid + 1, end, arr);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) {
            return 0; // Out of range
        }
        if (left <= start && right >= end) {
            return tree[node]; // Fully within the range
        }
        int mid = (start + end) / 2;
        int leftSum = query(2 * node, start, mid, left, right);
        int rightSum = query(2 * node + 1, mid + 1, end, left, right);
        return leftSum + rightSum;
    }

    void update(int node, int start, int end, int index, int newValue) {
        if (start == end) {
            // Leaf node, update the value
            tree[node] = newValue;
        } else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                // If the index to update is in the left subtree
                update(2 * node, start, mid, index, newValue);
            } else {
                // If the index to update is in the right subtree
                update(2 * node + 1, mid + 1, end, index, newValue);
            }
            // Update the parent node with the new values of child nodes
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n); // Size of the tree (4 times the size of the input array) to ensure it can accommodate all nodes.
        build(1, 0, n - 1, arr);
    }

    int queryRange(int left, int right) {
        if (left < 0 || right >= n || left > right) {
            return -1; // Invalid range
        }
        return query(1, 0, n - 1, left, right);
    }

    void updateElement(int index, int newValue) {
        if (index < 0 || index >= n) {
            return; // Invalid index
        }
        update(1, 0, n - 1, index, newValue);
    }
};

int main() {
    vector<int> v = {0, 1, 2, 3, 4};
    SegmentTree segmentTree(v);

    int sumInRange = segmentTree.queryRange(1, 3); // Sum of elements from index 1 to 3 (1 + 2 + 3)
    cout << "Sum in range [1, 3]: " << sumInRange << endl;

    // Update element at index 2 to a new value
    segmentTree.updateElement(2, 5);

    sumInRange = segmentTree.queryRange(1, 3); // Updated sum in range [1, 3] (1 + 5 + 3)
    cout << "Updated sum in range [1, 3]: " << sumInRange << endl;

    return 0;
}
