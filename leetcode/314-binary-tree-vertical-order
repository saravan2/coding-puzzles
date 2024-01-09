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
    map<int, vector<pair<int, int>>> verticalElements;
    void preorder(TreeNode* node, int x, int h) {
        if (!node) {
            return;
        }

        if (verticalElements.count(x)) {
            verticalElements[x].push_back(make_pair(h, node->val));
        } else {
            verticalElements[x] = {make_pair(h, node->val)};
        }

        preorder(node->left, x - 1, h + 1);
        preorder(node->right, x + 1, h + 1);
    }
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        preorder(root, 0, 0);
        vector<vector<int>> result;

        for (auto const&[x, y] : verticalElements) {
            vector<int> sorted;
            vector<pair<int, int>> elements = y;
            sort(elements.begin(), elements.end(), [](pair<int, int> a, pair<int, int> b) {
                return (a.first < b.first);
            });
            for (auto const& element : elements) {
                    sorted.push_back(element.second);
            }
            result.push_back(sorted);
            sorted.clear();
        }

        return result;
    }
};
