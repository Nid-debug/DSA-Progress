/*
    Problem: Longest Palindromic Subsequence
    Link: https://leetcode.com/problems/longest-palindromic-subsequence/

    Given a string s, return the length of the longest palindromic subsequence.

    Approaches:
    1. Recursion (LCS with reverse string)
    2. Memoization (Direct substring DP)
    3. Tabulation (Bottom-Up DP)
    4. Tabulation using LCS
    5. Space Optimization (LCS)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*=========================================================
    Approach 1: Recursion (LCS with reverse string)
    Time Complexity: Exponential
=========================================================*/

class Solution {
public:
    int solve(int i, int j, string& s, string& rev) {

        // base case
        if (i == 0 || j == 0) return 0;

        // characters match
        if (s[i - 1] == rev[j - 1]) return 1 + solve(i - 1, j - 1, s, rev);

        // characters don't match
        return max(solve(i - 1, j, s, rev), solve(i, j - 1, s, rev));
    }

    int longestPalindromeSubseq(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        int n = s.size();
        return solve(n, n, s, rev);
    }
};


/*=========================================================
    Approach 2: Memoization (Substring DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2)
=========================================================*/

class SolutionMemo {
public:
    int solve(int i, int j, string& s, vector<vector<int>>& dp) {

        if (i == j) return 1;
        if (i > j) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        if (s[i] == s[j]) return dp[i][j] = 2 + solve(i + 1, j - 1, s, dp);

        return dp[i][j] = max(solve(i + 1, j, s, dp), solve(i, j - 1, s, dp));
    }

    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(0, n - 1, s, dp);
    }
};


/*=========================================================
    Approach 3: Tabulation (Bottom-Up DP)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2)
=========================================================*/

class SolutionTab {
public:
    int longestPalindromeSubseq(string s) {

        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: single character
        for (int i = 0; i < n; i++) dp[i][i] = 1;

        // Fill DP table
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {

                if (s[i] == s[j])
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        return dp[0][n - 1];
    }
};


/*=========================================================
    Approach 4: Tabulation (LCS Approach)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2)
=========================================================*/

class SolutionTab2 {
public:
    int longestPalindromeSubseq(string s) {

        string rev = s;
        reverse(rev.begin(), rev.end());
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {

                if (s[i - 1] == rev[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][n];
    }
};


/*=========================================================
    Approach 5: Space Optimization (LCS)
    Time Complexity: O(n^2)
    Space Complexity: O(n)
=========================================================*/

class SolutionSpace {
public:
    int longestPalindromeSubseq(string s) {

        string rev = s;
        reverse(rev.begin(), rev.end());
        int n = s.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {

                if (s[i - 1] == rev[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }
        return prev[n];
    }
};


/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    Solution sol;
    SolutionMemo mem;
    SolutionTab tab;
    SolutionTab2 mat;
    SolutionSpace spa;

    string s = "bbbab";

    cout << "Recursive: " << sol.longestPalindromeSubseq(s) << endl;
    cout << "Memoization: " << mem.longestPalindromeSubseq(s) << endl;
    cout << "Tabulation: " << tab.longestPalindromeSubseq(s) << endl;
    cout << "LCS Tabulation: " << mat.longestPalindromeSubseq(s) << endl;
    cout << "Space Optimized: " << spa.longestPalindromeSubseq(s) << endl;
    return 0;
}