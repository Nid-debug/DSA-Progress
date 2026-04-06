/*
    Problem: Minimum Insertions to Make a String Palindrome
    Link: https://leetcode.com/problems/minimum-insertions-to-make-a-string-palindrome/

    Given a string s, return the minimum number of insertions
    needed to make it a palindrome.

    Key Idea:
    Minimum Insertions = n - LPS (Longest Palindromic Subsequence)

    And:
    LPS(s) = LCS(s, reverse(s))

    Approaches:
    1. Memoization (LCS)
    2. Tabulation (LCS)
    3. Space Optimization (LCS)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down LCS)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2) + recursion stack
=========================================================*/

class Solution {
public:
    int lcs(int i, int j, string& s, string& rev, vector<vector<int>>& dp) {

        if (i == 0 || j == 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        if (s[i - 1] == rev[j - 1]) return dp[i][j] = 1 + lcs(i - 1, j - 1, s, rev, dp);

        else
            return dp[i][j] = max(lcs(i - 1, j, s, rev, dp), lcs(i, j - 1, s, rev, dp));
    }

    int minInsertions(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return n - lcs(n, n, s, rev, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up LCS)
    Time Complexity: O(n^2)
    Space Complexity: O(n^2)
=========================================================*/

class SolutionTab {
public:
    int minInsertions(string s) {

        string rev = s;
        reverse(rev.begin(), rev.end());

        int i = s.size();
        int j = rev.size();

        vector<vector<int>> dp(i + 1, vector<int>(j + 1, 0));

        for (int a = 1; a <= i; a++) {
            for (int b = 1; b <= j; b++) {

                if (s[a - 1] == rev[b - 1])
                    dp[a][b] = 1 + dp[a - 1][b - 1];
                else
                    dp[a][b] = max(dp[a - 1][b], dp[a][b - 1]);
            }
        }
        return i - dp[i][j];
    }
};

/*=========================================================
    Approach 3: Space Optimization (1D DP - LCS)
    Time Complexity: O(n^2)
    Space Complexity: O(n)
=========================================================*/

class SolutionSpace {
public:
    int minInsertions(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());

        int i = s.size();
        int j = rev.size();

        vector<int> prev(j + 1, 0), curr(j + 1, 0);

        for (int a = 1; a <= i; a++) {
            for (int b = 1; b <= j; b++) {

                if (s[a - 1] == rev[b - 1])
                    curr[b] = 1 + prev[b - 1];
                else
                    curr[b] = max(prev[b], curr[b - 1]);
            }
            prev = curr;
        }
        return i - prev[j];
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;

    string s = "leetcode";

    cout << "Memoization: " << sol.minInsertions(s) << endl;
    cout << "Tabulation: " << tab.minInsertions(s) << endl;
    cout << "Space Optimized: " << spa.minInsertions(s) << endl;
    return 0;
}