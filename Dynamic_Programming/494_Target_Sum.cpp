/*
    Problem: Target Sum
    Link: https://leetcode.com/problems/target-sum/

    Given an array nums and a target,
    assign '+' or '-' to each number such that
    the expression evaluates to target.

    Trick:
    Convert to subset sum problem:
        s1 - s2 = target
        s1 + s2 = totalSum

    => s1 = (totalSum + target) / 2

    So problem becomes:
    Count subsets with sum = s1

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up DP)
    3. Space Optimization (1D DP)
*/

#include <iostream>
#include <vector>
using namespace std;


/*=========================================================
    Approach 1: Memoization (Top-Down DP)
    Time Complexity: O(n * target)
    Space Complexity: O(n * target) + O(n)
=========================================================*/

class SolutionMemo {
public:
    int solve(int idx, vector<int>& nums, int target, vector<vector<int>>& dp) {

        // Base case
        if (idx == 0) {
            if (target == 0 && nums[0] == 0) return 2; 
            if (target == 0) return 1;
            if (target == nums[0]) return 1;
            return 0;
        }

        if (dp[idx][target] != -1) return dp[idx][target];

        int notTake = solve(idx - 1, nums, target, dp);
        int take = 0;
        if (nums[idx] <= target) take = solve(idx - 1, nums, target - nums[idx], dp);

        return dp[idx][target] = take + notTake;
    }

    int findTargetSumWays(vector<int>& nums, int target) {

        int totalSum = 0;
        for (int x : nums) totalSum += x;

        // Invalid cases
        if ((totalSum + target) % 2 != 0) return 0;
        if ((totalSum + target) < 0) return 0;

        int newTarget = (totalSum + target) / 2;

        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(newTarget + 1, -1));

        return solve(n - 1, nums, newTarget, dp);
    }
};


/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * target)
    Space Complexity: O(n * target)
=========================================================*/

class SolutionTab {
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        int totalSum = 0;
        for (int x : nums) totalSum += x;

        if ((totalSum + target) % 2 != 0) return 0;
        if ((totalSum + target) < 0) return 0;

        int newTarget = (totalSum + target) / 2;
        int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(newTarget + 1, 0));

        // Base case
        if (nums[0] == 0) dp[0][0] = 2;
        else dp[0][0] = 1;
        if (nums[0] != 0 && nums[0] <= newTarget) dp[0][nums[0]] = 1;

        for (int i = 1; i < n; i++) {
            for (int tar = 0; tar <= newTarget; tar++) {

                int notTake = dp[i - 1][tar];
                int take = 0;
                if (nums[i] <= tar) take = dp[i - 1][tar - nums[i]];

                dp[i][tar] = take + notTake;
            }
        }
        return dp[n - 1][newTarget];
    }
};


/*=========================================================
    Approach 3: Space Optimization (1D DP)
    Time Complexity: O(n * target)
    Space Complexity: O(target)
=========================================================*/

class SolutionSpaceOptimized {
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        int totalSum = 0;
        for (int x : nums) totalSum += x;

        if ((totalSum + target) % 2 != 0) return 0;
        if ((totalSum + target) < 0) return 0;

        int newTarget = (totalSum + target) / 2;
        int n = nums.size();

        vector<int> prev(newTarget + 1, 0);

        // Base case
        if (nums[0] == 0) prev[0] = 2;
        else prev[0] = 1;
        if (nums[0] != 0 && nums[0] <= newTarget) prev[nums[0]] = 1;

        for (int i = 1; i < n; i++) {
            for (int tar = newTarget; tar >= 0; tar--) {

                int notTake = prev[tar];
                int take = 0;
                if (nums[i] <= tar) take = prev[tar - nums[i]];

                prev[tar] = take + notTake;
            }
        }
        return prev[newTarget];
    }
};


/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {

    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;

    SolutionMemo memo;
    SolutionTab tab;
    SolutionSpaceOptimized spaceOpt;

    cout << "Memoization: " << memo.findTargetSumWays(nums, target) << endl;
    cout << "Tabulation: " << tab.findTargetSumWays(nums, target) << endl;
    cout << "Space Optimized: " << spaceOpt.findTargetSumWays(nums, target) << endl;
    return 0;
}