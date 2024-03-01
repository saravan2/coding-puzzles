/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }

        unordered_map<Node*, Node*> origtocopy;

        Node* node = head;
        while (node) {
            origtocopy[node] = new Node(node->val);
            node = node->next;
        }

        node = head;
        while (node) {
            origtocopy[node]->next = origtocopy[node->next];
            origtocopy[node]->random = origtocopy[node->random];
            node = node->next;
        }
        return origtocopy[head];
        
    }
};/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }

        unordered_map<Node*, Node*> origtocopy;

        Node* node = head;
        while (node) {
            origtocopy[node] = new Node(node->val);
            node = node->next;
        }

        node = head;
        while (node) {
            origtocopy[node]->next = origtocopy[node->next];
            origtocopy[node]->random = origtocopy[node->random];
            node = node->next;
        }
        return origtocopy[head];
        
    }
};