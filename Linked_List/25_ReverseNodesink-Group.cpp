// LeetCode 25. Reverse Nodes in k-Group
// Time Complexity: O(n)
// Space Complexity: O(1)

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;

        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prevGroupEnd = dummy;
        ListNode* curr = head;

        while (true) {
            // Step 1: Check if there are at least k nodes remaining
            ListNode* check = curr;
            for (int i = 0; i < k; i++) {
                if (!check) return dummy->next; // not enough nodes
                check = check->next;
            }

            // Step 2: Reverse k nodes
            ListNode* prev = nullptr;
            ListNode* next = nullptr;
            ListNode* groupStart = curr;

            for (int i = 0; i < k; i++) {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            // Step 3: Connect reversed part
            prevGroupEnd->next = prev;   // 'prev' is new head of this group
            groupStart->next = curr;     // 'curr' is start of next group
            prevGroupEnd = groupStart;   // move groupEnd pointer ahead
        }

        return dummy->next;
    }
};