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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || !head->next || left == right) {
            return head;
        }
        ListNode* prev = nullptr;
        ListNode* curr = head;
        for (int i = 1; i < left && curr != nullptr; i++) {
            prev = curr;
            curr = curr->next;
        }
        ListNode* leftofleftnode = prev;
        ListNode* leftnode = curr;
        ListNode* next = nullptr;
        for (int i = left; i <= right && curr != nullptr; i++) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        if (leftofleftnode) {
            leftofleftnode->next = prev;
        } else {
            head = prev;
        }
        leftnode->next = curr;
        return head;
    }
};