// LeetCode 61. Rotate List
// Time Complexity: O(n)
// Space Complexity: O(1)

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;
        
        ListNode* tail = head;
        int length = 1;
        while (tail->next) {
            tail = tail->next;
            length++;
        }
        
        k = k % length;
        if (k == 0) {
            return head;
        }
        
        ListNode* newTail = head;
        for (int i = 0; i < length - k - 1; i++) {
            newTail = newTail->next;
        }
        
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;  
        tail->next = head;        
        
        return newHead;
    }
};