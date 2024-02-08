class Solution {
    struct segmentTree {
        vector<int> tree;
        int n;
        
        void init(int _n) {
            this->n = _n;
            tree.resize(4*n, 0);
        }

        void build(int start, int end, int node, vector<int>& v) {
            if (start == end) {
                tree[node] = v[start];
                return;
            }
            int mid = (start + end)/2;
            build(start, mid, 2*node+1, v);
            build(mid+1, end, 2*node+2, v);
            tree[node] = max(tree[2*node+1], tree[2*node+2]);
        }

        void update(int start, int end, int node, int index, int newValue) {
            if (start == end) {
                tree[node] = newValue;
            } else {
                int mid = (start + end)/2;
                if (index <= mid) {
                    update(start, mid, 2*node+1, index, newValue);
                } else {
                    update(mid+1, end, 2*node+2, index, newValue);
                }
                tree[node] = max(tree[2*node+1], tree[2*node+2]);
            }
        }

        int query(int start, int end, int node, int l, int r) {
            if (l > end || r < start) {
                return INT_MIN;
            }
            if ((l <= start) && (r >=end)) {
                return tree[node];
            }
            int mid = (start + end)/2;
            int leftMax = query(start, mid, 2*node+1, l, r);
            int rightMax = query(mid+1, end, 2*node+2, l, r);
            return max(leftMax, rightMax);
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        segmentTree st;
        vector<int> maxValues;
        st.init(n);
        st.build(0, n-1, 0, nums);
        for (int i = 0; i < (n-k+1); i++) {
            maxValues.push_back(st.query(0, n-1, 0, i, i+k-1));
        }
        return maxValues;
    }
};