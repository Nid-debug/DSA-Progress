class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return nullptr;

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* meet = nullptr;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                meet = slow;
                break;
            }
        }

        if (meet == nullptr)
            return nullptr;

        slow = head;
        while (slow != meet) {
            slow = slow->next;
            meet = meet->next;
        }

        return slow;
    }
};