#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int solve(int i, int j, string& s, string& t, vector<vector<int>>& dp) {
        if (j == 0) return 1;

        if (i == 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        if (s[i-1] == t[j-1]) return dp[i][j] = solve(i-1, j-1, s, t, dp) + solve(i-1, j, s, t, dp);

        return dp[i][j] = solve(i-1, j, s, t, dp);
    }

    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return solve(n, m, s, t, dp);
    }
};

class SolutionTab {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        vector<vector<long long>> dp(n+1, vector<long long>(m+1, 0));

        for (int i = 0; i <= n; i++) dp[i][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i-1] == t[j-1])
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                else
                    dp[i][j] = dp[i-1][j];

                dp[i][j] = min(dp[i][j], (long long)INT_MAX);
            }
        }
        return (int)dp[n][m];
    }
};

class SolutionSpace {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        vector<long long> prev(m+1, 0), curr(m+1, 0);

        prev[0] = 1;

        for (int i = 1; i <= n; i++) {
            curr[0] = 1;
            for (int j = 1; j <= m; j++) {
                if (s[i-1] == t[j-1])
                    curr[j] = prev[j-1] + prev[j];
                else
                    curr[j] = prev[j];

                curr[j] = min(curr[j], (long long)INT_MAX);
            }
            prev = curr;
        }
        return (int)prev[m];
    }
};

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;
    string s = "rabbbit";
    string t = "rabbit";
    cout << sol.numDistinct(s, t) << endl;
    cout << tab.numDistinct(s, t) << endl;
    cout << spa.numDistinct(s, t) << endl;
}