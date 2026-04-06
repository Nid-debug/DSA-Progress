/*
    Problem: Minimum Path Sum
    Link: https://leetcode.com/problems/minimum-path-sum/

    Given a grid filled with non-negative numbers,
    find a path from top-left to bottom-right
    which minimizes the sum of all numbers along its path.

    You can only move right or down.

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up 2D DP)
    3. Space Optimization (1D DP)
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down DP)
    Time Complexity: O(m * n)
    Space Complexity: O(m * n) + recursion stack
=========================================================*/

class SolutionMemo {
private:
    int solve(int row, int col, vector<vector<int>>& grid, vector<vector<int>>& dp) {

        // Base case: start cell
        if (row == 0 && col == 0) return grid[0][0];

        // Out of bounds
        if (row < 0 || col < 0) return INT_MAX;

        // Already computed
        if (dp[row][col] != -1) return dp[row][col];

        int up = solve(row - 1, col, grid, dp);
        int left = solve(row, col - 1, grid, dp);

        return dp[row][col] = grid[row][col] + min(up, left);
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, -1));

        return solve(m - 1, n - 1, grid, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up 2D DP)
    Time Complexity: O(m * n)
    Space Complexity: O(m * n)
=========================================================*/

class SolutionTab {
public:
    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Base case
        dp[0][0] = grid[0][0];

        // First row
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        // First column
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        // Fill remaining cells
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {

                int up = dp[i - 1][j];
                int left = dp[i][j - 1];

                dp[i][j] = grid[i][j] + min(up, left);
            }
        }
        return dp[m - 1][n - 1];
    }
};


/*=========================================================
    Approach 3: Space Optimization (1D DP)
    Time Complexity: O(m * n)
    Space Complexity: O(n)
=========================================================*/

class SolutionSpaceOptimized {
public:
    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        vector<int> prev(n, 0);

        // Initialize first row
        prev[0] = grid[0][0];
        for (int j = 1; j < n; j++) {
            prev[j] = prev[j - 1] + grid[0][j];
        }

        // Process remaining rows
        for (int i = 1; i < m; i++) {

            vector<int> curr(n, 0);

            // First column
            curr[0] = prev[0] + grid[i][0];

            for (int j = 1; j < n; j++) {

                int up = prev[j];
                int left = curr[j - 1];

                curr[j] = grid[i][j] + min(up, left);
            }
            prev = curr;
        }
        return prev[n - 1];
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    SolutionMemo memo;
    SolutionTab tab;
    SolutionSpaceOptimized spaceOpt;

    cout << "Memoization: " << memo.minPathSum(grid) << endl;
    cout << "Tabulation: " << tab.minPathSum(grid) << endl;
    cout << "Space Optimized: " << spaceOpt.minPathSum(grid) << endl;

    return 0;
}
