#include <iostream>
#include <vector>
using namespace std;

/*
===================================================
Problem: House Robber (LeetCode 198)

At each house, you have two choices:
1. Pick the current house -> nums[i] + dp[i-2]
2. Skip the current house -> dp[i-1]

We progressively optimize from:
Recursion + Memoization → Tabulation → Space Optimization
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
    int solve(int i, const vector<int>& nums, vector<int>& dp) {
        if (i == 0) return nums[0];
        if (i < 0) return 0;

        if (dp[i] != -1) return dp[i];

        int pick = nums[i] + solve(i - 2, nums, dp);
        int notPick = solve(i - 1, nums, dp);

        return dp[i] = max(pick, notPick);
    }

public:
    int rob(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        vector<int> dp(n, -1);
        return solve(n - 1, nums, dp);
    }
};


/*
---------------------------------------------------
Approach 2: Tabulation (Bottom-Up DP)
Time: O(n)
Space: O(n)
---------------------------------------------------
*/

class SolutionTab {
public:
    int rob(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n);

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            int pick = nums[i] + dp[i - 2];
            int notPick = dp[i - 1];

            dp[i] = max(pick, notPick);
        }

        return dp[n - 1];
    }
};


/*
---------------------------------------------------
Approach 3: Space Optimized DP
Time: O(n)
Space: O(1)
---------------------------------------------------
*/

class Solution {
public:
    int rob(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int prev2 = nums[0];                     // dp[i-2]
        int prev1 = max(nums[0], nums[1]);       // dp[i-1]

        for (int i = 2; i < n; i++) {
            int pick = nums[i] + prev2;
            int notPick = prev1;

            int curr = max(pick, notPick);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};


int main() {
    vector<int> nums = {1, 2, 3, 1};

    SolutionMemo memo;
    SolutionTab tab;
    Solution spaceOpt;

    cout << "Memoization: " << memo.rob(nums) << endl;
    cout << "Tabulation: " << tab.rob(nums) << endl;
    cout << "Space Optimized: " << spaceOpt.rob(nums) << endl;

    return 0;
}
