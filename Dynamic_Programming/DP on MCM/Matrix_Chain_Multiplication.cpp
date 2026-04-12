/*
    Problem: Matrix Chain Multiplication (MCM)

    Given an array arr[] of size N where:
    - The dimension of the i-th matrix is arr[i-1] x arr[i]

    Goal:
    Find the minimum number of multiplications needed to multiply the chain.

    Approach:
    - Partition DP
    - Try every partition point 'k'
    - Take minimum cost

    Time Complexity: O(N^3)
    Space Complexity: O(N^2)
*/

#include <iostream>
#include <vector>
using namespace std;

// Memoization Solution
class SolutionMemo {
public:
    int solve(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {

        // Base case: single matrix
        if (i == j) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        int mini = 1e9;
        for (int k = i; k < j; k++) {
            int steps = arr[i - 1] * arr[k] * arr[j] + solve(i, k, arr, dp) + solve(k + 1, j, arr, dp);
            mini = min(mini, steps);
        }
        return dp[i][j] = mini;
    }

    int matrixMultiplication(vector<int>& arr, int N) {
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return solve(1, N - 1, arr, dp);
    }
};

// Tabulation Solution
class SolutionTab {
public:
    int matrixMultiplication(vector<int>& arr, int N) {

        vector<vector<int>> dp(N, vector<int>(N, 0));
        // Base case: single matrix cost = 0
        for (int i = 1; i < N; i++) dp[i][i] = 0;

        // Fill DP table
        for (int i = N - 1; i >= 1; i--) {
            for (int j = i + 1; j < N; j++) {

                int mini = 1e9;
                for (int k = i; k < j; k++) {

                    int steps = arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j];
                    mini = min(mini, steps);
                }
                dp[i][j] = mini;
            }
        }
        return dp[1][N - 1];
    }
};

int main() {
    SolutionMemo sol;
    SolutionTab tab;
    vector<int> arr = {10, 15, 20, 25};
    int N = arr.size();
    cout << "Memoization: " << sol.matrixMultiplication(arr, N) << endl;
    cout << "Tabulation: " << tab.matrixMultiplication(arr, N) << endl;
    return 0;
}