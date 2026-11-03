#include <vector>
#include <algorithm>
using namespace std;

/*
📊 LeetCode 1793: Maximum Score of a Good Subarray

Problem:
You are given an integer array nums and an index k.

A subarray [i, j] is called good if i <= k <= j.

The score of a subarray is:

    score = minimum element in the subarray * length of the subarray

Return the maximum possible score among all good subarrays.

Approach: Greedy + Two Pointers

🧠 Intuition:
The subarray must always contain index k.

We start with the smallest possible subarray [k, k].
Its minimum is nums[k], and its score is nums[k].

Then, we expand the subarray toward the left or right until
the entire array is covered.

At every step:
- i represents the left boundary.
- j represents the right boundary.
- currentMin stores the minimum element in nums[i...j].
- maxi stores the maximum score found so far.

🧠 Key Greedy Idea:
When both sides can be expanded, compare the elements just
outside the current subarray:

    nums[i - 1] and nums[j + 1]

Expand toward the side with the larger element.

⚠️ Why?
The current score depends on both the subarray length and
its minimum value. Expanding toward the larger neighboring
element gives us a better chance of preserving the minimum
while increasing the length.

If one side reaches an array boundary, expand the other side.

🎯 Algorithm:
1. Initialize i = k and j = k.
2. Set currentMin = nums[k].
3. Set maxi = nums[k].
4. While the subarray can still expand:
   a. If i == 0, move j right.
   b. Else if j == n - 1, move i left.
   c. Else if nums[i - 1] > nums[j + 1], move i left.
   d. Otherwise, move j right.
   e. Update currentMin using nums[i] and nums[j].
   f. Calculate the current score:
          currentMin * (j - i + 1)
   g. Update maxi with the maximum score.
5. Return maxi.

⏱ Time Complexity: O(N)
Each pointer moves at most N - 1 times in total.

📦 Space Complexity: O(1)
Only a constant number of variables are used.

⚠️ Pattern to Remember:
Greedy + Two Pointers + Expand Around a Required Index

When a subarray must contain a specific index, start at that
index and expand while maintaining the information needed
to evaluate each candidate subarray.
*/

class Solution
{
public:
    int maximumScore(vector<int> &nums, int k)
    {
        int n = nums.size();
        int i = k;
        int j = k;

        int currentMin = nums[k];
        int maxi = nums[k];

        while (i > 0 || j < n - 1)
        {
            if (i == 0)
            {
                j++;
            }
            else if (j == n - 1)
            {
                i--;
            }
            else if (nums[i - 1] > nums[j + 1])
            {
                i--;
            }
            else
            {
                j++;
            }

            currentMin = min({currentMin, nums[i], nums[j]});

            maxi = max(maxi, currentMin * (j - i + 1));
        }
        return maxi;
    }
};