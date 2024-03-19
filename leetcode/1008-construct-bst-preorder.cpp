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
private:
    TreeNode* build(vector<int>& preorder, int pstart, int pend, vector<int>& inorder, int istart, int iend, unordered_map<int, int>& inorderValueToIndex) {
        if (pstart > pend || istart > iend) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[pstart]);
        int rootInorderIndex = inorderValueToIndex[preorder[pstart]];
        int numNodesInLeftTree = rootInorderIndex - istart;

        root->left = build(preorder, (pstart + 1), (pstart + numNodesInLeftTree), inorder, istart, (rootInorderIndex - 1), inorderValueToIndex);
        root->right = build(preorder, (pstart + numNodesInLeftTree + 1), pend, inorder, (rootInorderIndex + 1), iend, inorderValueToIndex);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderValueToIndex;
        for (int i = 0; i < inorder.size(); i++) {
            inorderValueToIndex[inorder[i]] = i;
        }
        TreeNode* root = build(preorder, 0, (preorder.size() - 1), inorder, 0, (inorder.size() - 1), inorderValueToIndex);
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        vector<int> inorder = preorder;
        sort(inorder.begin(), inorder.end());
        return buildTree(preorder, inorder);
    }
};