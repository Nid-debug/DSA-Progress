/*
    Problem: Unique Paths II
    Link: https://leetcode.com/problems/unique-paths-ii/

    Given an m x n grid with obstacles (1 represents obstacle),
    return the number of unique paths from top-left to bottom-right.

    You can only move right or down.

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up 2D DP)
    3. Space Optimization (1D DP)
*/

#include <iostream>
#include <vector>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down DP)
    Time Complexity: O(m * n)
    Space Complexity: O(m * n) + recursion stack
=========================================================*/

class SolutionMemo {
private:
    int solve(int row, int col, vector<vector<int>>& grid, vector<vector<int>>& dp) {

        // Out of bounds
        if (row < 0 || col < 0) return 0;

        // Obstacle cell
        if (grid[row][col] == 1) return 0;

        // Reached starting cell
        if (row == 0 && col == 0) return 1;

        // Already computed
        if (dp[row][col] != -1) return dp[row][col];

        int up = solve(row - 1, col, grid, dp);
        int left = solve(row, col - 1, grid, dp);

        return dp[row][col] = up + left;
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // If start or end is blocked → no path
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) return 0;

        vector<vector<int>> dp(m, vector<int>(n, -1));

        return solve(m - 1, n - 1, obstacleGrid, dp);
    }
};


/*=========================================================
    Approach 2: Tabulation (Bottom-Up 2D DP)
    Time Complexity: O(m * n)
    Space Complexity: O(m * n)
=========================================================*/

class SolutionTab {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) return 0;

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Initialize first column
        for (int i = 0; i < m; i++) {
            if (obstacleGrid[i][0] == 1) break;
            dp[i][0] = 1;
        }

        // Initialize first row
        for (int j = 0; j < n; j++) {
            if (obstacleGrid[0][j] == 1) break;
            dp[0][j] = 1;
        }

        // Fill remaining cells
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {

                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;  // Obstacle cell
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
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
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) return 0;

        vector<int> prev(n, 0);

        // Initialize first row
        for (int j = 0; j < n; j++) {
            if (obstacleGrid[0][j] == 1) break;
            prev[j] = 1;
        }

        // Process remaining rows
        for (int i = 1; i < m; i++) {

            vector<int> curr(n, 0);

            // First column (can only come from above)
            if (obstacleGrid[i][0] == 0)
                curr[0] = prev[0];

            for (int j = 1; j < n; j++) {

                if (obstacleGrid[i][j] == 1) {
                    curr[j] = 0;
                } else {
                    int up = prev[j];
                    int left = curr[j - 1];
                    curr[j] = up + left;
                }
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
    vector<vector<int>> obstacleGrid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    SolutionMemo memo;
    SolutionTab tab;
    SolutionSpaceOptimized spaceOpt;

    cout << "Memoization: " << memo.uniquePathsWithObstacles(obstacleGrid) << endl;

    cout << "Tabulation: " << tab.uniquePathsWithObstacles(obstacleGrid) << endl;

    cout << "Space Optimized: " << spaceOpt.uniquePathsWithObstacles(obstacleGrid) << endl;

    return 0;
}
