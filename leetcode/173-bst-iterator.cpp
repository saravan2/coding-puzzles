/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
private:
    stack<TreeNode *> soFar;
    
    void addToStack(TreeNode *node) {
        while (node) {
            soFar.push(node);
            node = node->left;
        }
    }
    
public:
 
    
    BSTIterator(TreeNode* root) {
        addToStack(root);
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode *current = soFar.top();
        soFar.pop();
        if (current->right) {
            addToStack(current->right);
        }
        return current->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !soFar.empty();
    }

};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
