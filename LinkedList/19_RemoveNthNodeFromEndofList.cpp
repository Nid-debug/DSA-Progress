// LeetCode 19. Remove Nth Node From End of List
// Time Complexity: O(L)
// Space Complexity: O(1)

// APPROACH 1: Two-Pass Solution 
// Time: O(L), Space: O(1)
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // First pass: count the length
        int length = 0;
        ListNode* curr = head;
        while (curr) {
            length++;
            curr = curr->next;
        }
        
        // Edge case: removing the head
        if (n == length) {
            return head->next;
        }
        
        // Calculate position of node before the one to remove
        int stepsToTake = length - n - 1;
        
        // Second pass: find the prev node
        curr = head;
        for (int i = 0; i < stepsToTake; i++) {
            curr = curr->next;
        }
        
        // Remove the nth node from end
        curr->next = curr->next->next;
        
        return head;
    }
};


// APPROACH 2: One-Pass Without Dummy Node
// Time: O(L), Space: O(1)
class Solution3 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;
        
        // Move fast n steps ahead
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        
        // If fast is null, we need to remove the head
        if (!fast) {
            return head->next;
        }
        
        // Move both until fast reaches the last node
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        
        // slow is now at the node before the one to remove
        slow->next = slow->next->next;
        
        return head;
    }
};