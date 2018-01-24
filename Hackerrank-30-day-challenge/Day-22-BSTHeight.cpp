#include <iostream>
#include <cstddef>

using namespace std;	

class Node{
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d){
            data = d;
            left = NULL;
            right = NULL;
        }
};
class Solution{
    public:
  	Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            }
            else {
                Node* cur;
                if(data <= root->data){
                    cur = insert(root->left, data);
                    root->left = cur;
                }
                else{
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }
        int heightHelper(Node* node, int height) {
            
            if (!node || (!(node->left) && !(node->right))) {
                return height;
            }
            
            int leftHeight = 0, rightHeight = 0;
            if (node->left) {
                leftHeight = heightHelper(node->left, (height+1));
            }
            if (node->right) {
                rightHeight = heightHelper(node->right, (height+1));
            }
            if (leftHeight >= rightHeight) {
                return leftHeight;
            } else {
                return rightHeight;
            }
        }

	int getHeight(Node* root){
          int height = 0;
          return heightHelper(root, height);
        }
}; //End of Solution

int main() {
    Solution myTree;
    Node* root = NULL;
    int t;
    int data;

    cin >> t;

    while(t-- > 0){
        cin >> data;
        root = myTree.insert(root, data);
    }
    int height = myTree.getHeight(root);
    cout << height;

    return 0;
}