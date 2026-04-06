/*
    Problem: Unique Paths
    Link: https://leetcode.com/problems/unique-paths/

    Given an m x n grid, a robot starts at the top-left corner (0,0)
    and can only move either down or right at any point in time.
    Return the number of possible unique paths to reach (m-1, n-1).

    Approaches:
    1. Memoization (Top-Down)
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
    int solve(int row, int col, vector<vector<int>>& dp) {

        // Base Case: Reached starting cell
        if (row == 0 && col == 0)
            return 1;

        // Out of bounds
        if (row < 0 || col < 0)
            return 0;

        // Already computed
        if (dp[row][col] != -1) return dp[row][col];

        // Move from top and left
        int up = solve(row - 1, col, dp);
        int left = solve(row, col - 1, dp);

        return dp[row][col] = up + left;
    }

public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return solve(m - 1, n - 1, dp);
    }
};


/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP - 2D)
    Time Complexity: O(m * n)
    Space Complexity: O(m * n)
=========================================================*/

class SolutionTab {
public:
    int uniquePaths(int m, int n) {

        vector<vector<int>> dp(m, vector<int>(n, 1));

        // Fill remaining cells
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};


/*=========================================================
    Approach 3: Space Optimized (1D DP)
    Time Complexity: O(m * n)
    Space Complexity: O(n)
=========================================================*/

class SolutionSpaceOptimized {
public:
    int uniquePaths(int m, int n) {

        vector<int> prev(n, 1);  // First row initialized to 1

        for (int i = 1; i < m; i++) {

            vector<int> curr(n, 0);
            curr[0] = 1;  // First column always 1

            for (int j = 1; j < n; j++) {
                curr[j] = prev[j] + curr[j - 1];
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

    int m = 3, n = 7;

    SolutionMemo memo;
    SolutionTab tab;
    SolutionSpaceOptimized spaceOpt;

    cout << "Memoization: " << memo.uniquePaths(m, n) << endl;
    cout << "Tabulation: " << tab.uniquePaths(m, n) << endl;
    cout << "Space Optimized: " << spaceOpt.uniquePaths(m, n) << endl;

    return 0;
}
