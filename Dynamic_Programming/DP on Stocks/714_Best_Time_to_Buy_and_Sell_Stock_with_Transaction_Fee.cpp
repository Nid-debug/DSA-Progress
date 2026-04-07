/*
    Problem: Best Time to Buy and Sell Stock with Transaction Fee
    Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

    You can make unlimited transactions,
    but each transaction has a fixed fee.

    State:
        idx → current day
        buy → 1 (can buy), 0 (can sell)

    Key Change:
        Subtract fee when SELLING

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
    int solve(int idx, int buy, vector<int>& prices, int fee, vector<vector<int>>& dp) {

        if (idx >= prices.size()) return 0;

        if (dp[idx][buy] != -1) return dp[idx][buy];

        if (buy) {
            return dp[idx][buy] = max(-prices[idx] + solve(idx + 1, 0, prices, fee, dp), solve(idx + 1, 1, prices, fee, dp));
        }

        return dp[idx][buy] = max(prices[idx] - fee + solve(idx + 1, 1, prices, fee, dp), solve(idx + 1, 0, prices, fee, dp));
    }

    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solve(0, 1, prices, fee, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * 2)
    Space Complexity: O(n)
=========================================================*/

class SolutionTab {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int idx = n - 1; idx >= 0; idx--) {
            for (int buy = 0; buy <= 1; buy++) {

                if (buy) {
                    dp[idx][buy] = max(-prices[idx] + dp[idx + 1][0], dp[idx + 1][1]);
                }
                else {
                    dp[idx][buy] = max(prices[idx] - fee + dp[idx + 1][1], dp[idx + 1][0]);
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
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<int> front1(2, 0);  // dp[idx+1]
        vector<int> curr(2, 0);    // dp[idx]

        for (int idx = n - 1; idx >= 0; idx--) {

            curr[1] = max(-prices[idx] + front1[0], front1[1]);

            curr[0] = max(prices[idx] - fee + front1[1], front1[0]);

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
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;

    cout << "Memoization: " << sol.maxProfit(prices, fee) << endl;
    cout << "Tabulation: " << tab.maxProfit(prices, fee) << endl;
    cout << "Space Optimized: " << spa.maxProfit(prices, fee) << endl;
    return 0;
}