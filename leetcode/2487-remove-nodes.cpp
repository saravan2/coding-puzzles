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
    ListNode* removeNodes(ListNode* head) {
        deque<ListNode*> mono_dq;
        ListNode* node = head;
        
        while(node) {
            while (!mono_dq.empty() && mono_dq.back()->val < node->val)
                mono_dq.pop_back();
            mono_dq.push_back(node);
            node = node->next;
        }
        head = mono_dq.front();
        mono_dq.pop_front();
        node = head;

        while(!mono_dq.empty()) {
            node->next = mono_dq.front();
            node = node->next;
            mono_dq.pop_front();
        }
        node->next = nullptr;
        return head;
    }
};