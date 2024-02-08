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
    vector<ListNode*> splitCircularLinkedList(ListNode* list) {
        ListNode* head = list;
        int len = 1;
        for (; list->next != head; list = list->next, len++)
        ;
        ListNode* last = list;
        list = head;
        for (int i = (len + 1) >> 1; i > 1; list = list->next, i--)
        ;
        ListNode* head2 = list->next;
        last->next = head2;
        list->next = head;
        return {head, head2};
    }
};