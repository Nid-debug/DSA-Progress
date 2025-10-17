// LeetCode 328. Odd Even Linked List
// Time Complexity: O(n)
// Space Complexity: O(1)

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* odd = head;              // First odd node (1st node)
        ListNode* even = head->next;       // First even node (2nd node)
        ListNode* evenHead = even;         // To connect later

        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;        // Connect current odd to next odd
            odd = odd->next;               // Move odd forward
            even->next = odd->next;        // Connect current even to next even
            even = even->next;             // Move even forward
        }

        odd->next = evenHead;              // Attach even list after odd list
        return head;
    }
};