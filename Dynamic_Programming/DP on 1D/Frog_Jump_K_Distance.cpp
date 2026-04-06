#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {

// Memoization
// private:
//     int solve(int i, vector<int>& heights, int k, vector<int>& dp) {
//         if (i == 0) return 0;

//         int minSteps = INT_MAX;

//         if(dp[i] != -1) return dp[i];

//         for (int j = 1; j <= k; j++) {
//             // Ensure we don't go below index 0
//             if (i - j >= 0) {
//                 int jumpCost = solve(i - j, heights, k, dp) + abs(heights[i] - heights[i - j]);
//                 minSteps = min(minSteps, jumpCost);
//             }
//         }

//         return dp[i] = minSteps;
//     }

// Tabulation
public:
    int frogJumpK(vector<int>& heights, int k) {
        int n = heights.size();
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;

        for(int i = 1; i < n; i++) {

            for (int j = 1; j <= k; j++) {
                if (i - j >= 0) {
                int currentJumpCost = dp[i-j] + abs(heights[i] - heights[i-j]);
                dp[i] = min(dp[i], currentJumpCost);
            }
        }
    }
    return dp[n-1];
  }
};

int main() {
    Solution sol;
    vector<int> heights = {10, 5, 20, 0, 15};
    int k = 2;
    cout << sol.frogJumpK(heights, k) << endl;
}