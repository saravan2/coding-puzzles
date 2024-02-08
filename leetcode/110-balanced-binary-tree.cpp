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
public:
    int checkHeight(TreeNode* node, bool& balanced) {
        if (!node || !balanced)
            return 0;
        
        int left = checkHeight(node->left, balanced);
        int right = checkHeight(node->right, balanced);
        if (abs(left - right) > 1)
            balanced = false;
        
        return 1 + max(left, right);
    }
    bool isBalanced(TreeNode* root) {
        bool balanced = true;
        checkHeight(root, balanced);
        return balanced;
    }
};