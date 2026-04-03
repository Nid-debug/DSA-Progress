/*
    Problem: Best Time to Buy and Sell Stock II
    Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

    You can buy and sell multiple times (unlimited transactions),
    but you must sell before buying again.

    State:
        idx → current day
        buy → 1 (can buy), 0 (can sell)

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up DP)
    3. Space Optimization (2 arrays)
    4. Space Optimization (variables only)
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
    int solve(int idx, int buy, vector<int>& prices, int n, vector<vector<long>>& dp) {
        if(idx == n) return 0;

        if(dp[idx][buy] != -1) return dp[idx][buy];

        int profit = 0;
        if(buy) {
            profit = max(-prices[idx] + solve(idx+1, 0, prices, n, dp), 0 + solve(idx+1, 1, prices, n, dp));
        }
        else {
            profit = max(prices[idx] + solve(idx+1, 1, prices, n, dp), 0 + solve(idx+1, 0, prices, n, dp));
        }
        return dp[idx][buy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<long>> dp(n, vector<long>(2, -1));
        return solve(0, 1, prices, n, dp);
    }
};


/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * 2)
    Space Complexity: O(n * 2)
=========================================================*/

class SolutionTab {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<long>> dp(n+1, vector<long>(2, 0));
        dp[n][0] = dp[n][1] = 0;

        for(int idx = n-1; idx >= 0; idx--) {
            for(int buy = 0; buy <= 1; buy++) {
                long profit = 0;
                if(buy) {
                    profit = max(-prices[idx] + dp[idx+1][0], 0 + dp[idx+1][1]);
                }
                else {
                    profit = max(prices[idx] + dp[idx+1][1], 0 + dp[idx+1][0]);
                }
                dp[idx][buy] = profit;
            }
        }
        return dp[0][1];
    }
};

/*=========================================================
    Approach 3: Space Optimization (Arrays)
    Time Complexity: O(n)
    Space Complexity: O(1)
=========================================================*/

class SolutionSpace {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<long> ahead(2, 0), curr(2, 0);
        ahead[0] = ahead[1] = 0;

        for(int idx = n-1; idx >= 0; idx--) {
            for(int buy = 0; buy <= 1; buy++) {
                long profit = 0;
                if(buy) {
                    profit = max(-prices[idx] + ahead[0], 0 + ahead[1]);
                }
                else {
                    profit = max(prices[idx] + ahead[1], 0 + ahead[0]);
                }
                curr[buy] = profit;
            }
            ahead = curr;
        }
        return ahead[1];
    }
};

/*=========================================================
    Approach 4: Space Optimization (Variables Only)
    Time Complexity: O(n)
    Space Complexity: O(1)
=========================================================*/

class SolutionSpace2 {
public:
    int maxProfit(vector<int>& prices) {

        long aheadNotBuy, aheadBuy, currBuy, currNotBuy;
        aheadNotBuy = aheadBuy = 0;

        for(int idx = prices.size()-1; idx >= 0; idx--) {

            currNotBuy = max(prices[idx] + aheadBuy, 0 + aheadNotBuy);
            
            currBuy = max(-prices[idx] + aheadNotBuy, 0 + aheadBuy);
                
            aheadBuy = currBuy;
            aheadNotBuy = currNotBuy;
        }
        return aheadBuy;
    }
};