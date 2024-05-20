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
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        std::deque<TreeNode*> dq;
        dq.push_back(root);
        int level = 0;
        while (!dq.empty()) {
            int lsize = dq.size();
            while (lsize--) {
                TreeNode* node = dq.front();
                dq.pop_front();
                TreeNode* left = node->left;
                TreeNode* right = node->right;
                if (!left && !right) {
                    return (level + 1);
                } 
                
                if (left) {
                    dq.push_back(left);
                }
                
                if (right) {
                    dq.push_back(right);
                }
            }
            level++;
        }
        return level;
    }
};