#include <vector>
#include <queue>

using namespace std;

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> min_heap(cmp);
        
        // Push the first node of each list into the heap
        for (ListNode* list : lists) {
            if (list != nullptr) {
                min_heap.push(list);
            }
        }
        
        ListNode dummy;
        ListNode* tail = &dummy;
        
        while (!min_heap.empty()) {
            ListNode* smallest = min_heap.top();
            min_heap.pop();
            
            tail->next = smallest;
            tail = tail->next;
            
            if (smallest->next != nullptr) {
                min_heap.push(smallest->next);
            }
        }
        
        return dummy.next;
    }
};
