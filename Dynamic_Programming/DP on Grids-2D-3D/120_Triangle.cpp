/*
    Problem: Triangle
    Link: https://leetcode.com/problems/triangle/

    Given a triangle array, return the minimum path sum
    from top to bottom.

    For each step, you may move to:
        - Directly below
        - Diagonally below-right

    Approaches:
    1. Memoization (Top-Down DP)
    2. Tabulation (Bottom-Up DP)
    3. Space Optimization (1D DP)
*/

#include <iostream>
#include <vector>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2) + recursion stack
=========================================================*/

class SolutionMemo {
private:
    int solve(int row, int col, vector<vector<int>>& triangle, vector<vector<int>>& dp) {

        // Base case: Last row
        if (row == triangle.size() - 1) return triangle[row][col];

        // Already computed
        if (dp[row][col] != -1) return dp[row][col];

        int down = triangle[row][col] + solve(row + 1, col, triangle, dp);

        int diagonal = triangle[row][col] + solve(row + 1, col + 1, triangle, dp);

        return dp[row][col] = min(down, diagonal);
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {

        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        return solve(0, 0, triangle, dp);
    }
};


/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2)
=========================================================*/

class SolutionTab {
public:
    int minimumTotal(vector<vector<int>>& triangle) {

        int n = triangle.size();

        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: copy last row
        for (int col = 0; col < triangle[n - 1].size(); col++) {
            dp[n - 1][col] = triangle[n - 1][col];
        }

        // Fill from bottom to top
        for (int row = n - 2; row >= 0; row--) {
            for (int col = 0; col <= row; col++) {

                int down = dp[row + 1][col];
                int diagonal = dp[row + 1][col + 1];

                dp[row][col] = triangle[row][col] + min(down, diagonal);
            }
        }
        return dp[0][0];
    }
};


/*=========================================================
    Approach 3: Space Optimization (1D DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n)
=========================================================*/

class SolutionSpaceOptimized {
public:
    int minimumTotal(vector<vector<int>>& triangle) {

        int n = triangle.size();

        // Start from the last row
        vector<int> dp = triangle[n - 1];

        // Move upwards
        for (int row = n - 2; row >= 0; row--) {
            for (int col = 0; col <= row; col++) {

                dp[col] = triangle[row][col] + min(dp[col], dp[col + 1]);
            }
        }
        return dp[0];
    }
};


/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    vector<vector<int>> triangle = {{2},{3, 4},{6, 5, 7},{4, 1, 8, 3}};
    SolutionMemo memo;
    SolutionTab tab;
    SolutionSpaceOptimized spaceOpt;

    cout << "Memoization: " << memo.minimumTotal(triangle) << endl;
    cout << "Tabulation: " << tab.minimumTotal(triangle) << endl;
    cout << "Space Optimized: " << spaceOpt.minimumTotal(triangle) << endl;

    return 0;
}
