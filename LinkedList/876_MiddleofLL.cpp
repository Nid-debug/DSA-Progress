class Solution {
public:
    // Function to find the middle node of a linked list
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head; // moves 1 step at a time
        ListNode* fast = head; // moves 2 steps at a time

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow; // slow is at the middle
    }
};