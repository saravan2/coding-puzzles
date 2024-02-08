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
    void buildInorderVector(TreeNode* node, vector<TreeNode *>& inOrder) {
        if (!node)
            return;

        if (node->left) {
            buildInorderVector(node->left, inOrder);
        } 
        
        inOrder.push_back(node);

        if (node->right) {
            buildInorderVector(node->right, inOrder);
        }
    }

    TreeNode* makeBalancedBST(int start, int end, vector<TreeNode *>& inOrder) {
        if (start > end) {
            return NULL;
        }

        int mid = start + (end - start) / 2;
        inOrder[mid]->left = makeBalancedBST(start, mid - 1, inOrder);
        inOrder[mid]->right = makeBalancedBST(mid + 1, end, inOrder);
        return inOrder[mid];
    }

public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<TreeNode *> inOrderVector;
        buildInorderVector(root, inOrderVector);
        int start = 0;
        int end = inOrderVector.size() - 1;
        return makeBalancedBST(start, end, inOrderVector);
    }
};