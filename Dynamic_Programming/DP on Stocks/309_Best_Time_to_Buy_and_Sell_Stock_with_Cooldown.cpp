/*
    Problem: Best Time to Buy and Sell Stock with Cooldown
    Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

    After you sell a stock, you cannot buy on the next day (cooldown of 1 day).

    State:
        idx → current day
        buy → 1 (can buy), 0 (can sell)

    Key Change:
        When selling → move to idx + 2 (skip one day)

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
    Time Complexity: O(n * 2)
    Space Complexity: O(n * 2) + recursion stack
=========================================================*/

class Solution {
public:
    int solve(int idx, int buy, vector<int>& prices, vector<vector<int>>& dp) {

        if (idx >= prices.size()) return 0;

        if (dp[idx][buy] != -1) return dp[idx][buy];

        if (buy) {
            return dp[idx][buy] = max(-prices[idx] + solve(idx + 1, 0, prices, dp), solve(idx + 1, 1, prices, dp));
        }

        return dp[idx][buy] = max(prices[idx] + solve(idx + 2, 1, prices, dp), solve(idx + 1, 0, prices, dp));
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solve(0, 1, prices, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * 2)
    Space Complexity: O(n)
=========================================================*/

class SolutionTab {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        for (int idx = n - 1; idx >= 0; idx--) {
            for (int buy = 0; buy <= 1; buy++) {

                if (buy) {
                    dp[idx][buy] = max(-prices[idx] + dp[idx + 1][0], dp[idx + 1][1]);
                }
                else {
                    dp[idx][buy] = max(prices[idx] + dp[idx + 2][1], dp[idx + 1][0]);
                }
            }
        }
        return dp[0][1];
    }
};

/*=========================================================
    Approach 3: Space Optimization
    Time Complexity: O(n)
    Space Complexity: O(1)
=========================================================*/

class SolutionSpace {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> front2(2, 0);  // dp[idx+2]
        vector<int> front1(2, 0);  // dp[idx+1]
        vector<int> curr(2, 0);    // dp[idx]

        for (int idx = n - 1; idx >= 0; idx--) {

            curr[1] = max(-prices[idx] + front1[0], front1[1]);

            curr[0] = max(prices[idx] + front2[1], front1[0]);

            front2 = front1;
            front1 = curr;
        }
        return front1[1];
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;
    vector<int> prices = {1, 2, 3, 0, 2};

    cout << "Memoization: " << sol.maxProfit(prices) << endl;
    cout << "Tabulation: " << tab.maxProfit(prices) << endl;
    cout << "Space Optimized: " << spa.maxProfit(prices) << endl;
    return 0;
}