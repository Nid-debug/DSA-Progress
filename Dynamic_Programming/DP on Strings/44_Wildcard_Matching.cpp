/*
    Problem: Wildcard Matching
    Link: https://leetcode.com/problems/wildcard-matching/

    Given a string s and pattern p:
    '?' → matches any single character
    '*' → matches any sequence (including empty)

    Return true if pattern matches entire string.

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
    Time Complexity: O(n * m)
    Space Complexity: O(n * m) + recursion stack
=========================================================*/

class Solution {
public:
    int solve(int i, int j, string& s, string& p, vector<vector<int>>& dp) {

        if (i == 0 && j == 0) return true;

        if (j == 0) return false;

        if (dp[i][j] != -1) return dp[i][j];

        // string exhausted, pattern must be all '*'
        if (i == 0) {
            for (int k = 1; k <= j; k++)
                if (p[k - 1] != '*') return false;
            return true;
        }

        // match or '?'
        if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
            return dp[i][j] = solve(i - 1, j - 1, s, p, dp);

        // '*'
        if (p[j - 1] == '*')
            return dp[i][j] = solve(i - 1, j, s, p, dp) || solve(i, j - 1, s, p, dp);

        return false;
    }

    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solve(n, m, s, p, dp);
    }
};


/*=========================================================
    Approach 2: Tabulation (Bottom-Up DP)
    Time Complexity: O(n * m)
    Space Complexity: O(n * m)
=========================================================*/

class SolutionTab {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = true;

        // string empty, pattern must be all '*'
        for (int j = 1; j <= m; j++)
            dp[0][j] = dp[0][j - 1] && p[j - 1] == '*';

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {

                if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];

                else if (p[j - 1] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];

                else dp[i][j] = false;
            }
        }
        return dp[n][m];
    }
};


/*=========================================================
    Approach 3: Space Optimization (1D DP)
    Time Complexity: O(n * m)
    Space Complexity: O(m)
=========================================================*/

class SolutionSpace {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<bool> prev(m + 1, false), curr(m + 1, false);

        prev[0] = true;

        // string empty, pattern must be all '*'
        for (int j = 1; j <= m; j++)
            prev[j] = prev[j - 1] && p[j - 1] == '*';

        for (int i = 1; i <= n; i++) {
            curr[0] = false;
            for (int j = 1; j <= m; j++) {

                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') curr[j] = prev[j - 1];

                else if (p[j - 1] == '*') curr[j] = prev[j] || curr[j - 1];

                else curr[j] = false;
            }
            prev = curr;
        }
        return prev[m];
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;
    string s = "aa";
    string p = "*";

    cout << "Memoization: " << sol.isMatch(s, p) << endl;
    cout << "Tabulation: " << tab.isMatch(s, p) << endl;
    cout << "Space Optimized: " << spa.isMatch(s, p) << endl;
    return 0;
}