#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int solve(int i, int j, string& word1, string& word2, vector<vector<int>>& dp) {

        if(i == 0) return j;
        if(j == 0) return i;

        if(dp[i][j] != -1) return dp[i][j];

        if(word1[i-1] == word2[j-1]) return dp[i][j] = solve(i-1, j-1, word1, word2, dp);

        int replace = 1 + solve(i-1, j-1, word1, word2, dp);
        int remove = 1 + solve(i-1, j, word1, word2, dp);
        int insert = 1 + solve(i, j-1, word1, word2, dp);

        return dp[i][j] = min({replace, remove, insert});
    }

    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return solve(n, m, word1, word2, dp);
    }
};

class SolutionTab {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for(int j = 0; j <= m; j++) dp[0][j] = j;  // empty word1, insert j chars
        for(int i = 0; i <= n; i++) dp[i][0] = i;  // empty word2, delete i chars

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {

                if(word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];

                else dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
            }
        }
        return dp[n][m];
    }
};

class SolutionSpace {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<int> prev(m+1, 0), curr(m+1, 0);

        for(int j = 0; j <= m; j++) prev[j] = j;  // empty word1, insert j chars

        for(int i = 1; i <= n; i++) {
            curr[0] = i;
            for(int j = 1; j <= m; j++) {

                if(word1[i-1] == word2[j-1]) curr[j] = prev[j-1];
                
                else curr[j] = 1 + min({prev[j-1], prev[j], curr[j-1]});
            }
            prev = curr;
        }
        return prev[m];
    }
};

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;
    string word1 = "horse";
    string word2 = "ros";
    cout << sol.minDistance(word1, word2) << endl;
    cout << tab.minDistance(word1, word2) << endl;
    cout << spa.minDistance(word1, word2) << endl;
}