/*
    Problem: Delete Operation for Two Strings
    Link: https://leetcode.com/problems/delete-operation-for-two-strings/

    Given two strings, return the minimum number of deletions
    required to make them equal.

    Key Idea:
    Minimum Deletions = len(word1) + len(word2) - 2 * LCS(word1, word2)

    Approaches:
    1. Memoization (Top-Down LCS)
    2. Tabulation (Bottom-Up LCS)
    3. Space Optimization (1D DP)
*/

#include <iostream>
#include <vector>
using namespace std;

/*=========================================================
    Approach 1: Memoization (Top-Down LCS)
    Time Complexity: O(n * m)
    Space Complexity: O(n * m) + recursion stack
=========================================================*/

class Solution { 
public:
    int lcs(int i, int j, string& word1, string& word2, vector<vector<int>>& dp) {

        if (i == 0 || j == 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        if (word1[i - 1] == word2[j - 1])
            return dp[i][j] = 1 + lcs(i - 1, j - 1, word1, word2, dp);

        else
            return dp[i][j] = max(lcs(i - 1, j, word1, word2, dp), lcs(i, j - 1, word1, word2, dp));
    }

    int minDistance(string word1, string word2) {

        int n = word1.size();
        int s = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(s + 1, -1));
        return n + s - 2 * lcs(n, s, word1, word2, dp);
    }
};

/*=========================================================
    Approach 2: Tabulation (Bottom-Up LCS)
    Time Complexity: O(n * m)
    Space Complexity: O(n * m)
=========================================================*/

class SolutionTab {
public:
    int minDistance(string word1, string word2) {

        int i = word1.size();
        int j = word2.size();
        vector<vector<int>> dp(i + 1, vector<int>(j + 1, 0));

        for (int a = 1; a <= i; a++) {
            for (int b = 1; b <= j; b++) {

                if (word1[a - 1] == word2[b - 1])
                    dp[a][b] = 1 + dp[a - 1][b - 1];
                else
                    dp[a][b] = max(dp[a - 1][b], dp[a][b - 1]);
            }
        }
        return i + j - 2 * dp[i][j];
    }
};

/*=========================================================
    Approach 3: Space Optimization (1D DP)
    Time Complexity: O(n * m)
    Space Complexity: O(m)
=========================================================*/

class SolutionSpace {
public:
    int minDistance(string word1, string word2) {

        int i = word1.size();
        int j = word2.size();

        vector<int> prev(j + 1, 0), curr(j + 1, 0);

        for (int a = 1; a <= i; a++) {
            for (int b = 1; b <= j; b++) {

                if (word1[a - 1] == word2[b - 1])
                    curr[b] = 1 + prev[b - 1];
                else
                    curr[b] = max(prev[b], curr[b - 1]);
            }
            prev = curr;
        }
        return i + j - 2 * prev[j];
    }
};

/*=========================================================
    Main Function (For Local Testing)
=========================================================*/

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;

    string word1 = "leetcode";
    string word2 = "etco";

    cout << "Memoization: " << sol.minDistance(word1, word2) << endl;
    cout << "Tabulation: " << tab.minDistance(word1, word2) << endl;
    cout << "Space Optimized: " << spa.minDistance(word1, word2) << endl;
    return 0;
}