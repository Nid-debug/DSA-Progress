/*
    Problem: Minimum Cost to Cut a Stick

    Approach: Partition DP

    --------------------------------------------------
    Memoization:
    Time Complexity: O(n^3)
    Space Complexity: O(n^2) + O(n)   // dp + recursion stack
    --------------------------------------------------

    Tabulation:
    Time Complexity: O(n^3)
    Space Complexity: O(n^2)
    --------------------------------------------------

    Idea:
    - Add boundaries (0 and n)
    - Sort cuts
    - dp[i][j] = minimum cost to cut between cuts[i] and cuts[j]

    Transition:
    - Try every partition k:
      cost = (cuts[j] - cuts[i]) + dp[i][k] + dp[k][j]
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Memoization
class Solution {
public:
    int solve(int i, int j, vector<int>& cuts, vector<vector<int>>& dp) {

        if (j - i <= 1) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        int mini = 1e9;
        for (int k = i + 1; k < j; k++) {

            int cost = (cuts[j] - cuts[i]) + solve(i, k, cuts, dp) + solve(k, j, cuts, dp);
            mini = min(mini, cost);
        }
        return dp[i][j] = mini;
    }

    int minCost(int n, vector<int>& cuts) {

        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        int m = cuts.size();
        vector<vector<int>> dp(m, vector<int>(m, -1));
        return solve(0, m - 1, cuts, dp);
    }
};

// Tabulation
class SolutionTab {
public:
    int minCost(int n, vector<int>& cuts) {

        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        int m = cuts.size();
        vector<vector<int>> dp(m, vector<int>(m, 0));

        for (int i = m - 1; i >= 0; i--) {
            for (int j = i + 2; j < m; j++) {

                int mini = 1e9;
                for (int k = i + 1; k < j; k++) {
                    int cost = (cuts[j] - cuts[i]) + dp[i][k] + dp[k][j];
                    mini = min(mini, cost);
                }
                dp[i][j] = mini;
            }
        }
        return dp[0][m - 1];
    }
};
