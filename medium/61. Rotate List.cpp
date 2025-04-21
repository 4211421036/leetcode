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
        if (head == nullptr || head->next == nullptr || k == 0) {
            return head;
        }
        
        // Calculate the length of the list and find the tail
        int length = 1;
        ListNode* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
            length++;
        }
        
        // Connect the tail to the head to make it circular
        tail->next = head;
        
        // Find the new tail: (length - k % length - 1) steps from head
        int effective_k = k % length;
        int steps = length - effective_k - 1;
        ListNode* new_tail = head;
        for (int i = 0; i < steps; ++i) {
            new_tail = new_tail->next;
        }
        
        // The new head is the next node after new_tail
        ListNode* new_head = new_tail->next;
        
        // Break the circle
        new_tail->next = nullptr;
        
        return new_head;
    }
};
