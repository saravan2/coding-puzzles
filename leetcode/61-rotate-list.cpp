/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {

public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr  || head->next == nullptr) {
            return head;
        } 
        int n = 0;
        ListNode *node = head, *next = head->next;
        while (node) {
            node = node->next;
            n++;
        }
        int traverse = n - (k % n);
        if (traverse == n) {
            return head;
        } else {
            ListNode* prevHead = head;
            next = head;
            for (int i = 0; i < traverse; i++) {
                node = next;
                next = node->next;
            }
            node->next = nullptr;
            head = next;
            node = head;
            next = node->next;
            while(next) {
                node = next;
                next = node->next;
            }
            node->next = prevHead;
            return head;
        }
    }
};