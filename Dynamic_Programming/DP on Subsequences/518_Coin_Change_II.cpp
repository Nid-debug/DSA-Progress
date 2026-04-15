/*
    Problem: Coin Change II
    Link: https://leetcode.com/problems/coin-change-ii/

    Given coins and an amount,
    return the total number of ways to make that amount.

    This is an Unbounded Knapsack (Count Ways) problem.

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
    Time Complexity: O(n * amount)
    Space Complexity: O(n * amount) + O(n)
=========================================================*/

class Solution
{
public:
    int solve(int idx, int amount, vector<int> &coins, vector<vector<int>> &dp)
    {

        // Base cases
        if (amount == 0)
            return 1;
        if (idx < 0 || amount < 0)
            return 0;

        // Memo check
        if (dp[idx][amount] != -1)
            return dp[idx][amount];

        int notTake = solve(idx - 1, amount, coins, dp);
        int take = 0;
        if (coins[idx] <= amount)
            take = solve(idx, amount - coins[idx], coins, dp);

        return dp[idx][amount] = take + notTake;
    }

    int change(int amount, vector<int> &coins)
    {

        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));

        return solve(coins.size() - 1, amount, coins, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * amount)
    Space Complexity: O(n * amount)
=========================================================*/

class SolutionTab
{
public:
    int change(int amount, vector<int> &coins)
    {

        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

        // Base case
        for (int amt = 0; amt <= amount; amt++)
        {
            if (coins[0] == 0)
                return 0; // Edge case
            if (amt % coins[0] == 0)
                dp[0][amt] = 1;
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int amt = 0; amt <= amount; amt++)
            {

                int notTake = dp[idx - 1][amt];
                int take = 0;
                if (coins[idx] <= amt)
                    take = dp[idx][amt - coins[idx]];

                dp[idx][amt] = take + notTake;
            }
        }
        return dp[n - 1][amount];
    }
};

/*=========================================================
    Approach 3: Space Optimization (1D DP)
    Time Complexity: O(n * amount)
    Space Complexity: O(amount)
=========================================================*/

class SolutionSpace
{
public:
    int change(int amount, vector<int> &coins)
    {

        int n = coins.size();
        vector<int> prev(amount + 1, 0);

        // Base case
        for (int amt = 0; amt <= amount; amt++)
        {
            if (amt % coins[0] == 0)
                prev[amt] = 1;
        }

        for (int idx = 1; idx < n; idx++)
        {
            for (int amt = 0; amt <= amount; amt++)
            {

                int notTake = prev[amt];
                int take = 0;
                if (coins[idx] <= amt)
                    take = prev[amt - coins[idx]];

                prev[amt] = take + notTake;
            }
        }
        return prev[amount];
    }
};