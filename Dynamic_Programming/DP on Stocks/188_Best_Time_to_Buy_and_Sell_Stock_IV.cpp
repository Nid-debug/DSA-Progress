/*
    Problem: Best Time to Buy and Sell Stock IV
    Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

    You can complete at most K transactions.

    State:
        idx → current day
        buy → 1 (can buy), 0 (can sell)
        cap → remaining transactions (K)

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up DP)
    3. Space Optimization
*/

#include <iostream>
#include <vector>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down DP)
    Time Complexity: O(n * 2 * k)
    Space Complexity: O(n * 2 * k) + recursion stack
=========================================================*/

class Solution {
public:
    int solve(vector<int>& prices, int idx, int buy, int cap, vector<vector<vector<int>>>& dp) {

        if (idx == prices.size() || cap == 0) return 0;

        if (dp[idx][buy][cap] != -1) return dp[idx][buy][cap];

        if (buy) {
            return dp[idx][buy][cap] = max(-prices[idx] + solve(prices, idx + 1, 0, cap, dp), solve(prices, idx + 1, 1, cap, dp));
        }
        else {
            return dp[idx][buy][cap] = max(prices[idx] + solve(prices, idx + 1, 1, cap - 1, dp), solve(prices, idx + 1, 0, cap, dp));
        }
    }

    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k+1, -1)));
        return solve(prices, 0, 1, k, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * 2 * k)
    Space Complexity: O(n * 2 * k)
=========================================================*/

class SolutionTab {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        for (int idx = n - 1; idx >= 0; idx--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {

                    if (buy) {
                        dp[idx][buy][cap] = max(-prices[idx] + dp[idx + 1][0][cap], dp[idx + 1][1][cap]);
                    }
                    else {
                        dp[idx][buy][cap] = max(prices[idx] + dp[idx + 1][1][cap - 1], dp[idx + 1][0][cap]);
                    }
                }
            }
        }
        return dp[0][1][k];
    }
};

/*=========================================================
    Approach 3: Space Optimization
    Time Complexity: O(n * k)
    Space Complexity: O(k)
=========================================================*/

class SolutionSpace {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> next(2, vector<int>(k + 1, 0));
        vector<vector<int>> curr(2, vector<int>(k + 1, 0));

        for (int idx = n - 1; idx >= 0; idx--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {

                    if (buy) {
                        curr[buy][cap] = max(-prices[idx] + next[0][cap], next[1][cap]);
                    }
                    else {
                        curr[buy][cap] = max(prices[idx] + next[1][cap - 1], next[0][cap]);
                    }
                }
            }
            next = curr;
        }
        return next[1][k];
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    int k = 2;
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;

    cout << "Memoization: " << sol.maxProfit(k, prices) << endl;
    cout << "Tabulation: " << tab.maxProfit(k, prices) << endl;
    cout << "Space Optimized: " << spa.maxProfit(k, prices) << endl;
    return 0;
}