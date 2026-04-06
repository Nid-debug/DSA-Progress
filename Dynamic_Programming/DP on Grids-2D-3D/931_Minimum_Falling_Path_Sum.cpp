/*
    Problem: Minimum Falling Path Sum
    Link: https://leetcode.com/problems/minimum-falling-path-sum/

    Given an n x n matrix, return the minimum sum of any falling path.

    A falling path starts at any element in the first row
    and moves to the next row choosing one of:
        - directly below
        - diagonally left
        - diagonally right

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up DP)
    3. Space Optimization (1D DP)
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2) + recursion stack
=========================================================*/

class SolutionMemo {
private:
    int solve(int row, int col, vector<vector<int>>& matrix, vector<vector<int>>& dp) {

        int n = matrix.size();

        // Out of bounds
        if (col < 0 || col >= n) return INT_MAX;

        // Base case: last row
        if (row == n - 1) return matrix[row][col];

        // Already computed
        if (dp[row][col] != -1) return dp[row][col];

        int down = solve(row + 1, col, matrix, dp);
        int leftDiag = solve(row + 1, col - 1, matrix, dp);
        int rightDiag = solve(row + 1, col + 1, matrix, dp);

        return dp[row][col] = matrix[row][col] + min(down, min(leftDiag, rightDiag));
    }

public:
    int minFallingPathSum(vector<vector<int>>& matrix) {

        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        int ans = INT_MAX;
        // Try starting from every column in first row
        for (int col = 0; col < n; col++) {
            ans = min(ans, solve(0, col, matrix, dp));
        }
        return ans;
    }
};


/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2)
=========================================================*/

class SolutionTab {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {

        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> dp(n, vector<int>(m, 0));

        // First row = base
        dp[0] = matrix[0];

        for (int row = 1; row < n; row++) {
            for (int col = 0; col < m; col++) {

                int up = dp[row - 1][col];
                int leftDiag = (col > 0) ? dp[row - 1][col - 1] : INT_MAX;
                int rightDiag = (col < m - 1) ? dp[row - 1][col + 1] : INT_MAX;

                dp[row][col] = matrix[row][col] + min(up, min(leftDiag, rightDiag));
            }
        }
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};


/*=========================================================
    Approach 3: Space Optimization (1D DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n)
=========================================================*/

class SolutionSpaceOptimized {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {

        int n = matrix.size();
        int m = matrix[0].size();

        vector<int> prev = matrix[0];

        for (int row = 1; row < n; row++) {
            vector<int> curr(m);

            for (int col = 0; col < m; col++) {

                int up = prev[col];
                int leftDiag = (col > 0) ? prev[col - 1] : INT_MAX;
                int rightDiag = (col < m - 1) ? prev[col + 1] : INT_MAX;

                curr[col] = matrix[row][col] + min(up, min(leftDiag, rightDiag));
            }
            prev = curr;
        }
        return *min_element(prev.begin(), prev.end());
    }
};


/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {

    vector<vector<int>> matrix = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };

    SolutionMemo memo;
    SolutionTab tab;
    SolutionSpaceOptimized spaceOpt;

    cout << "Memoization: "<< memo.minFallingPathSum(matrix) << endl;
    cout << "Tabulation: " << tab.minFallingPathSum(matrix) << endl;
    cout << "Space Optimized: " << spaceOpt.minFallingPathSum(matrix) << endl;

    return 0;
}
