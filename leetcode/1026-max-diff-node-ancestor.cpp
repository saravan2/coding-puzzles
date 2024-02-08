/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int max_diff = 0;
    void solve_diff(TreeNode* node, int minimum, int maximum) {
        if (!node)
            return;

        max_diff = max(max_diff, max(abs(minimum - node->val), abs(maximum - node->val)));
        minimum = min(minimum, node->val);
        maximum = max(maximum, node->val);
        solve_diff(node->left, minimum, maximum);
        solve_diff(node->right, minimum, maximum);
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        if (!root) {
            return 0;
        }
        solve_diff(root, root->val, root->val);
        return max_diff;
    }
};