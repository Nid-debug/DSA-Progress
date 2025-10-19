// LeetCode 160. Intersection of Two Linked List
// Time Complexity: O(n + m)
// Space Complexity: O(1)

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return nullptr;

        ListNode* ptrA = headA;
        ListNode* ptrB = headB;

        while(ptrA != ptrB) {
            ptrA = ptrA ? ptrA->next : headB;
            ptrB = ptrB ? ptrB->next : headA;
        }

        return ptrA;
    }
};