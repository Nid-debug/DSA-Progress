#include <iostream>
#include <vector>
using namespace std;

class SolutionMemo {
public:
    int solve(int i, int j, string& str1, string& str2, vector<vector<int>>& dp) {

        if(i == 0 || j == 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        if(str1[i-1] == str2[j-1]) return dp[i][j] = 1 + solve(i-1, j-1, str1, str2, dp);

        return 0;
    }

    int longestCommonSubstring(string str1, string str2) {
        int m = str1.size(), n = str2.size();
        int ans = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                ans = max(ans, solve(i, j, str1, str2, dp));

        return ans;
    }
};

class SolutionTab {
public:
    int longestCommonSubstring(string str1, string str2) {
        int m = str1.size(), n = str2.size();
        int ans = 0;
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if(str1[i-1] == str2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                    ans = max(ans, dp[i][j]);
                } 
                else dp[i][j] = 0;
            }
        }
        return ans;
    }
};

class SolutionSpace {
public:
    int longestCommonSubstring(string str1, string str2) {
        int m = str1.size(), n = str2.size();
        vector<int> prev(m+1, 0), curr(n+1, 0);
        int ans = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i-1] == str2[j-1]) {
                    curr[j] = 1 + prev[j-1];
                    ans = max(ans, curr[j]);
                }
                else curr[j] = 0;  // chain broken
            }
            prev = curr;
            // reset curr to 0 for next row
            fill(curr.begin(), curr.end(), 0);
        }
        return ans;
    }
};
