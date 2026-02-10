// LeetCode 2095. Delete the Middle Node of Linked List
// Time Complexity: O(N)
// Space Complexity: O(1)

// APPROACH 1: Two-Pass Solution 
// Time: O(N), Space: O(1)
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
        return nullptr;

        int length = 0;
        ListNode* curr = head;

        while(curr) {
            length++;
            curr = curr->next;
        }

        int steps = (length / 2) - 1;

        curr = head;
        for(int i = 0; i < steps; i++) {
            curr = curr->next;
        }

        curr->next = curr->next->next;
        return head;
    }
};

// APPROACH 2: One-Pass Solution
// Time: O(N), Space: O(1)
class Solution {
public : 
    ListNode* deleteMiddle(ListNode* head) {
    if (head == nullptr || head->next == nullptr)
    return nullptr;

    ListNode* slow = head;
    ListNode* fast = head->next->next;

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }

    slow->next = slow->next->next;
    return head;
    }
};