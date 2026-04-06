/*
    Problem: Best Time to Buy and Sell Stock III
    Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

    You can complete at most 2 transactions.

    State:
        idx → current day
        buy → 1 (can buy), 0 (can sell)
        cap → remaining transactions (max = 2)

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up DP)
    3. Space Optimization (3D → 2D)
    4. Optimized Variables (Greedy DP)
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down DP)
    Time Complexity: O(n * 2 * 3)
    Space Complexity: O(n * 2 * 3) + recursion stack
=========================================================*/

class Solution {
public:
    int solve(int idx, int buy, vector<int>& prices, int cap, vector<vector<vector<int>>>& dp) {

        if (idx == prices.size() || cap == 0) return 0;

        if (dp[idx][buy][cap] != -1) return dp[idx][buy][cap];

        int profit = 0;

        if (buy) {
            profit = max(-prices[idx] + solve(idx + 1, 0, prices, cap, dp), 0 + solve(idx + 1, 1, prices, cap, dp));
        }
        else {
            profit = max(prices[idx] + solve(idx + 1, 1, prices, cap - 1, dp), 0 + solve(idx + 1, 0, prices, cap, dp)
            );
        }
        return dp[idx][buy][cap] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
        return solve(0, 1, prices, 2, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * 2 * 3)
    Space Complexity: O(n * 2 * 3)
=========================================================*/

class SolutionTab {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        for (int idx = n - 1; idx >= 0; idx--) {
            for (int buy = 0; buy <= 1; buy++) {

                for (int cap = 1; cap <= 2; cap++) {

                    if (buy) {
                        dp[idx][buy][cap] = max(-prices[idx] + dp[idx + 1][0][cap], 0 + dp[idx + 1][1][cap]);
                    }
                    else {
                        dp[idx][buy][cap] = max(prices[idx] + dp[idx + 1][1][cap - 1], 0 + dp[idx + 1][0][cap]);
                    }
                }
            }
        }
        return dp[0][1][2];
    }
};

/*=========================================================
    Approach 3: Space Optimization (2D DP)
    Time Complexity: O(n)
    Space Complexity: O(1)
=========================================================*/

class SolutionSpace {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> ahead(2, vector<int>(3, 0));

        for (int idx = n - 1; idx >= 0; idx--) {
            vector<vector<int>> temp = ahead;

            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {

                    if (buy) {
                        temp[buy][cap] = max(-prices[idx] + ahead[0][cap], ahead[1][cap]);
                    }
                    else {
                        temp[buy][cap] = max(prices[idx] + ahead[1][cap - 1], ahead[0][cap]);
                    }
                }
            }
            ahead = temp;
        }
        return ahead[1][2];
    }
};

/*=========================================================
    Approach 4: Optimized Variables (Greedy DP)
    Time Complexity: O(n)
    Space Complexity: O(1)
=========================================================*/

class SolutionSpace2 {
public:
    int maxProfit(vector<int>& prices) {

        int buy1 = INT_MIN, buy2 = INT_MIN;
        int sell1 = 0, sell2 = 0;

        for (int price : prices) {

            buy1 = max(buy1, -price);
            sell1 = max(sell1, buy1 + price);
            buy2 = max(buy2, sell1 - price);
            sell2 = max(sell2, buy2 + price);
        }
        return sell2;
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;
    SolutionSpace2 spaa;
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};

    cout << "Memoization: " << sol.maxProfit(prices) << endl;
    cout << "Tabulation: " << tab.maxProfit(prices) << endl;
    cout << "Space Optimized (2D): " << spa.maxProfit(prices) << endl;
    cout << "Optimized Variables: " << spaa.maxProfit(prices) << endl;
    return 0;
}