/**
* Definition for a single linked list.
* struct ListNode { 
*     int val;
*     ListNode *next;
*     ListNode() : val(0), next(nullptr) {}
*     ListNode(int x) : val(x), next(NULL) {}
*     ListNode(int x, ListNode *next) : val(x), next(next) {}
* };
*/
class Solution {
public:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = NULL;
        ListNode* node = head;
        ListNode* next = NULL;
        while (node) {
            next = node->next;
            node->next = prev;
            prev = node;
            node = next;
        }
        return prev;
    }
    ListNode* doubleIt(ListNode* head) {
        if (!head) return NULL;
        ListNode* rnode = reverse(head);
        int sum = (rnode->val * 2);
        int carry = sum / 10;
        ListNode* node = new ListNode(sum % 10);
        ListNode* result = node;
        ListNode* prev = node;
        rnode = rnode->next;
        while(rnode || carry) {
            sum = 0;
            if (rnode) {
                sum = (rnode->val * 2);
                rnode = rnode->next;
            }
            sum += carry;
            carry = sum / 10;
            node = new ListNode(sum % 10);
            prev->next = node;
            prev = node;
        }
        return reverse(result);
    }
};