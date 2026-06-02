/*
🔄 Problem: Reorder List

Given the head of a singly linked list:

L0 → L1 → L2 → ... → Ln

Reorder it into:

L0 → Ln → L1 → Ln-1 → L2 → Ln-2 ...

You must modify the list in-place.

-----------------------------------------------------

💡 Approach:

👉 Key Idea:

The reorder naturally breaks into 3 steps:

1. Find the middle of the linked list
2. Reverse the second half
3. Merge both halves alternately

-----------------------------------------------------

🧠 Step 1: Find Middle

Use Slow-Fast Pointer technique:

slow moves 1 step
fast moves 2 steps

When fast reaches the end:
- slow will be at the middle

Example:

1 → 2 → 3 → 4 → 5

slow ends at 3

-----------------------------------------------------

🧠 Step 2: Reverse Second Half

Original:

3 → 4 → 5

Reverse:

5 → 4 → 3

Now we have:

First Half:
1 → 2 → 3

Second Half:
5 → 4 → 3

-----------------------------------------------------

🧠 Step 3: Merge Alternately

Take one node from first half,
then one node from second half.

Example:

1 → 2 → 3

5 → 4 → 3

After merging:

1 → 5 → 2 → 4 → 3

-----------------------------------------------------

⚠️ Key Insight:

Instead of repeatedly finding the last node
(which would be O(N²)),

we reverse the second half once and then
merge in O(N).

-----------------------------------------------------

⏱ Time Complexity:
- Finding middle: O(N)
- Reversing: O(N)
- Merging: O(N)

Total:
- O(N)

-----------------------------------------------------

📦 Space Complexity:
- O(1)

Only pointers are used.
No extra data structures.
*/

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // Step 1: Find the middle of the list
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse the second half of the list
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while (curr) {
            ListNode* nextTemp = curr->next; // store next node
            curr->next = prev;                // reverse pointer
            prev = curr;                      // move prev forward
            curr = nextTemp;                  // move curr forward
        }

        // Step 3: Merge the two halves
        ListNode* first = head;
        ListNode* second = prev; // start of reversed second half

        while (second) {
            ListNode* temp1 = first->next; // store next node of first half
            ListNode* temp2 = second->next; // store next node of second half

            first->next = second; // link first node to second
            second->next = temp1; // link second node to next of first

            first = temp1; // move first forward
            second = temp2; // move second forward
        }
    }
};