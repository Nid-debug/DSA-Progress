// LeetCode 121. Best Time to Buy and Sell Stock
// Category: Arrays, Dynamic Programming
// Problem: Given an array prices where prices[i] is the stock price on day i,
// find the maximum profit you can achieve by choosing a day to buy and a later day to sell.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ✅ Approach 1: Track minimum price (Greedy / One-pass)
    // Intuition: Buy at the lowest price seen so far, sell at today's price.
    int maxProfit(vector<int>& prices) {
        int buy = prices[0];   // minimum price seen so far
        int profit = 0;        // maximum profit

        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < buy) {
                buy = prices[i];  // found a better day to buy
            } else {
                profit = max(profit, prices[i] - buy); // potential profit
            }
        }
        return profit;
    }

    // ✅ Approach 2: Kadane’s Algorithm (DP way)
    // Intuition: Treat consecutive price differences as an array and
    // find the maximum subarray sum (max profit window).
    int maxProfitKadane(vector<int>& prices) {
        if (prices.size() <= 1) return 0;

        int currProfit = 0, maxProfit = 0;

        for (int i = 1; i < prices.size(); i++) {
            int diff = prices[i] - prices[i - 1]; // daily profit/loss
            currProfit = max(diff, currProfit + diff); // extend or restart
            maxProfit = max(maxProfit, currProfit);   // update best profit
        }
        return maxProfit;
    }
};

// Example usage
int main() {
    Solution sol;
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    cout << "Approach 1 (Min price tracking): " << sol.maxProfit(prices) << endl;
    cout << "Approach 2 (Kadane's Algorithm): " << sol.maxProfitKadane(prices) << endl;

    return 0;
}

/*
Output:
Approach 1 (Min price tracking): 5
Approach 2 (Kadane's Algorithm): 5

Time Complexity: O(n)
Space Complexity: O(1)
*/
