#include <vector>
using namespace std;

/*
📏 LeetCode 795: Number of Subarrays with Bounded Maximum

Problem:
Given an integer array nums and two integers left and right,
return the number of non-empty subarrays such that the maximum
element in each subarray lies in the range [left, right].

Approach: One-Pass Counting

Intuition:
For every index i, we want to count how many valid subarrays
end at index i.

We maintain two indices:

1. lastInvalid:
   The most recent index where nums[i] > right.
   Any subarray containing this element is invalid.

2. lastValid:
   The most recent index where nums[i] >= left.
   This marks the most recent element that can make the
   subarray's maximum reach at least left.

Key Idea:
A subarray ending at index i is valid if:
- It starts after lastInvalid.
- It includes at least one element >= left.

Therefore, when lastValid > lastInvalid, the number of
valid subarrays ending at index i is:

    lastValid - lastInvalid

Why?
Every starting index from lastInvalid + 1 through lastValid
produces a subarray whose maximum is within [left, right].

Algorithm:
1. Initialize result = 0.
2. Initialize lastValid = -1 and lastInvalid = -1.
3. Traverse nums from left to right.
4. If nums[i] > right, update lastInvalid = i.
5. If nums[i] >= left, update lastValid = i.
6. If lastValid > lastInvalid, add
   lastValid - lastInvalid to result.
7. Return result.

Example:
nums = [2, 1, 4, 3]
left = 2, right = 3

i = 0, nums[i] = 2:
lastValid = 0, lastInvalid = -1
Valid subarrays ending here = 0 - (-1) = 1
[2]

i = 1, nums[i] = 1:
lastValid = 0, lastInvalid = -1
Valid subarrays ending here = 1
[2, 1]

i = 2, nums[i] = 4:
lastInvalid = 2
lastValid = 0
No valid subarrays ending here.

i = 3, nums[i] = 3:
lastValid = 3, lastInvalid = 2
Valid subarrays ending here = 3 - 2 = 1
[3]

Total = 1 + 1 + 0 + 1 = 3

Time Complexity: O(N)
We traverse the array exactly once.

Space Complexity: O(1)
We use only a constant number of variables.

Pattern to Remember:
Subarray Counting + Bounded Maximum + Last Seen Indices
When counting subarrays with a constrained maximum, track
the most recent invalid element and the most recent element
that satisfies the lower bound.
*/

class Solution
{
public:
    int numSubarrayBoundedMax(vector<int> &nums, int left, int right)
    {
        int result = 0;
        int lastValid = -1;
        int lastInvalid = -1;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > right)
            {
                lastInvalid = i;
            }
            if (nums[i] >= left)
            {
                lastValid = i;
            }
            if (lastValid > lastInvalid)
            {
                result += (lastValid - lastInvalid);
            }
        }
        return result;
    }
};