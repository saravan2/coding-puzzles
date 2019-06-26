/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = NULL;
        ListNode* prev = NULL;
        int carry = 0;
        while (l1 || l2) {
            int first = (l1?l1->val:0);
            int second = (l2?l2->val:0);
            int sum = first + second + carry;
            carry = sum / 10;
            ListNode *node = new ListNode(sum%10);
            if (!result)
                result = node;
            if (prev)
                prev->next = node;
            prev = node;
            l1 = (l1?l1->next:NULL);
            l2 = (l2?l2->next:NULL);
        }
        if (carry) {
            ListNode *node = new ListNode(carry);
            prev->next = node;
        }
        return result;
    }
};
