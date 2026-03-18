/*
    Problem: Coin Change
    Link: https://leetcode.com/problems/coin-change/

    Given coins of different denominations and a total amount,
    return the fewest number of coins needed to make up that amount.
    If not possible, return -1.

    Approaches:
    1. Recursion (Exponential)
    2. Memoization (Top-Down DP)
    3. Tabulation (Bottom-Up DP)
    4. Space Optimization (1D DP)
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = 1e9;

/*=========================================================
    Approach 1: Recursion
    Time Complexity: Exponential
=========================================================*/

class SolutionRecursive {
public:
    int solve(int idx, vector<int>& coins, int amount) {

        // Base case
        if (idx == 0) {
            if (amount % coins[0] == 0)
                return amount / coins[0];
            return INF;
        }

        int notTake = solve(idx - 1, coins, amount);

        int take = INF;
        if (coins[idx] <= amount) {
            int sub = solve(idx, coins, amount - coins[idx]);
            if (sub != INF)
                take = 1 + sub;
        }

        return min(take, notTake);
    }

    int coinChange(vector<int>& coins, int amount) {
        int ans = solve(coins.size() - 1, coins, amount);
        return (ans >= INF) ? -1 : ans;
    }
};

/*=========================================================
    Approach 2: Memoization (Top-Down DP)
    Time Complexity: O(n * amount)
    Space Complexity: O(n * amount)
=========================================================*/

class SolutionMemo {
public:
    int solve(int idx, vector<int>& coins, int amount,
              vector<vector<int>>& dp) {

        if (idx == 0) {
            if (amount % coins[0] == 0)
                return amount / coins[0];
            return INF;
        }

        if (dp[idx][amount] != -1)
            return dp[idx][amount];

        int notTake = solve(idx - 1, coins, amount, dp);

        int take = INF;
        if (coins[idx] <= amount) {
            int sub = solve(idx, coins, amount - coins[idx], dp);
            if (sub != INF)
                take = 1 + sub;
        }

        return dp[idx][amount] = min(take, notTake);
    }

    int coinChange(vector<int>& coins, int amount) {

        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));

        int ans = solve(n - 1, coins, amount, dp);
        return (ans >= INF) ? -1 : ans;
    }
};

/*=========================================================
    Approach 3: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * amount)
    Space Complexity: O(n * amount)
=========================================================*/

class SolutionTab {
public:
    int coinChange(vector<int>& coins, int amount) {

        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, INF));

        // Base case
        for (int j = 0; j <= amount; j++) {
            if (j % coins[0] == 0)
                dp[0][j] = j / coins[0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= amount; j++) {

                int notTake = dp[i - 1][j];

                int take = INF;
                if (coins[i] <= j && dp[i][j - coins[i]] != INF)
                    take = 1 + dp[i][j - coins[i]];

                dp[i][j] = min(take, notTake);
            }
        }

        int ans = dp[n - 1][amount];
        return (ans >= INF) ? -1 : ans;
    }
};

/*=========================================================
    Approach 4: Space Optimization (1D DP)
    Time Complexity: O(n * amount)
    Space Complexity: O(amount)
=========================================================*/

class SolutionSpaceOptimized {
public:
    int coinChange(vector<int>& coins, int amount) {

        int n = coins.size();
        vector<int> dp(amount + 1, INF);

        // Base case
        for (int j = 0; j <= amount; j++) {
            if (j % coins[0] == 0) dp[j] = j / coins[0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= amount; j++) {

                int notTake = dp[j];

                int take = INF;
                if (coins[i] <= j && dp[j - coins[i]] != INF)
                    take = 1 + dp[j - coins[i]];

                dp[j] = min(take, notTake);
            }
        }
        int ans = dp[amount];
        return (ans >= INF) ? -1 : ans;
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    SolutionRecursive rec;
    SolutionMemo memo;
    SolutionTab tab;
    SolutionSpaceOptimized spaceOpt;

    cout << "Recursive: " << rec.coinChange(coins, amount) << endl;
    cout << "Memoization: " << memo.coinChange(coins, amount) << endl;
    cout << "Tabulation: " << tab.coinChange(coins, amount) << endl;
    cout << "Space Optimized: " << spaceOpt.coinChange(coins, amount) << endl;

    return 0;
}