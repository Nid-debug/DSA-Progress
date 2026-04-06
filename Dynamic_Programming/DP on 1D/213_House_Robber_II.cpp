#include <iostream>
#include <vector>
using namespace std;

/*
===================================================
Problem: House Robber II (LeetCode 213)

Houses are arranged in a circle.
So we cannot rob both first and last house.

We split into two cases:
1. Rob houses from index 0 to n-2
2. Rob houses from index 1 to n-1

Final Answer = max(case1, case2)

We show two approaches:
1. Memoization (Top-Down DP)
2. Space Optimized DP
===================================================
*/


/*
---------------------------------------------------
Approach 1: Memoization (Top-Down DP)
Time: O(n)
Space: O(n) + recursion stack
---------------------------------------------------
*/

class SolutionMemo {
private:
    int solve(int i, int start, const vector<int>& nums, vector<int>& dp) {
        if (i == start) return nums[start];
        if (i < start) return 0;

        if (dp[i] != -1) return dp[i];

        int pick = nums[i] + solve(i - 2, start, nums, dp);
        int notPick = solve(i - 1, start, nums, dp);

        return dp[i] = max(pick, notPick);
    }

public:
    int rob(const vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);

        vector<int> dp1(n, -1);
        vector<int> dp2(n, -1);

        // Case 1: Exclude last house
        int case1 = solve(n - 2, 0, nums, dp1);

        // Case 2: Exclude first house
        int case2 = solve(n - 1, 1, nums, dp2);

        return max(case1, case2);
    }
};


/*
---------------------------------------------------
Approach 2: Space Optimized DP
Time: O(n)
Space: O(1)
---------------------------------------------------
*/

class Solution {
private:
    int solveRange(int start, int end, const vector<int>& nums) {
        int n = end - start + 1;

        if (n == 1) return nums[start];

        int prev2 = nums[start];
        int prev1 = max(nums[start], nums[start + 1]);

        for (int i = 2; i < n; i++) {
            int pick = nums[start + i] + prev2;
            int notPick = prev1;

            int curr = max(pick, notPick);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

public:
    int rob(const vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);

        int case1 = solveRange(0, n - 2, nums);
        int case2 = solveRange(1, n - 1, nums);

        return max(case1, case2);
    }
};


int main() {
    vector<int> nums = {2, 3, 2};

    SolutionMemo memo;
    Solution spaceOpt;

    cout << "Memoization: " << memo.rob(nums) << endl;
    cout << "Space Optimized: " << spaceOpt.rob(nums) << endl;

    return 0;
}