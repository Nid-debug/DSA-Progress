#include <iostream>
#include <vector>
using namespace std;

/*
========================================
        Memoization (Top-Down)
========================================
Time Complexity: O(N^3)
Space Complexity: O(N^2) + O(N) recursion stack
*/

class Solution {
public:
    int solve(int i, int j, vector<int>& nums, vector<vector<int>>& dp) {
        if (i > j) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        int maxi = -1e9;
        for (int k = i; k <= j; k++) {
            int cost = nums[i - 1] * nums[k] * nums[j + 1] + solve(i, k - 1, nums, dp) + solve(k + 1, j, nums, dp);
            maxi = max(maxi, cost);
        }
        return dp[i][j] = maxi;
    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        return solve(1, n, nums, dp);
    }
};


/*
========================================
        Tabulation (Bottom-Up)
========================================
Time Complexity: O(N^3)
Space Complexity: O(N^2)
*/

class SolutionTab {
public:
    int maxCoins(vector<int>& nums) {

        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for (int i = n; i >= 1; i--) {
            for (int j = i; j <= n; j++) {

                int maxi = -1e9;
                for (int k = i; k <= j; k++) {
                    int cost = nums[i - 1] * nums[k] * nums[j + 1] + dp[i][k - 1] + dp[k + 1][j];
                    maxi = max(maxi, cost);
                }
                dp[i][j] = maxi;
            }
        }
        return dp[1][n];
    }
};