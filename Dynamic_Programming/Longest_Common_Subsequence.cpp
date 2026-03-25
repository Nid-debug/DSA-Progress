#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int solve(int i, int j, string& str1, string& str2, vector<vector<int>>& dp) {

        if(i < 0 || j < 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        if(str1[i] == str2[j]) return dp[i][j] = 1 + solve(i-1, j-1, str1, str2, dp);

        else return dp[i][j] = max(solve(i-1, j, str1, str2, dp), solve(i, j-1, str1, str2, dp));
    }

    int lcs(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n-1, m-1, str1, str2, dp);
    }
};

class SolutionTab {
public:
    int lcs(string str1, string str2) {
        int i = str1.size(), j = str2.size();
        vector<vector<int>> dp(i+1, vector<int>(j+1, 0));

        for (int a = 1; a <= i; a++) {
            for (int b = 1; b <= j; b++) {
                if (str1[a-1] == str2[b-1]) dp[a][b] = 1 + dp[a-1][b-1];

                else dp[a][b] = max(dp[a-1][b], dp[a][b-1]);
            }
        }
        return dp[i][j];
    }
};

class SolutionSpace {
public:
    int lcs(string str1, string str2) {
        int i = str1.size(), j = str2.size();
        vector<int> prev(j+1, 0), curr(j+1, 0);

        for (int a = 1; a <= i; a++) {
            for (int b = 1; b <= j; b++) {
                if (str1[a-1] == str2[b-1]) curr[b] = 1 + prev[b-1];
                
                else curr[b] = max(prev[b], curr[b-1]);
            }
            prev = curr;
        }
        return prev[j];
    }
};

int main() {
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;
    string str1 = "bdefg";
    string str2 = "bfg";
    cout << sol.lcs(str1, str2) << endl;
    cout << tab.lcs(str1, str2) << endl;
    cout << spa.lcs(str1, str2) << endl;
}