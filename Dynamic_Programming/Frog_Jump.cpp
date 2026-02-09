#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {

// Memorization
// private:
//     int solve(int i, vector<int>& heights, vector<int>& dp, int& n) {
//         if(i == 0) return 0;

//         if(dp[i] != -1) return dp[i];

//         int left = solve(i - 1, heights, dp, n) + abs(heights[i] - heights[i-1]);
//         int right = INT_MAX;

//         if(i > 1) {
//             right = solve(i - 2, heights, dp, n) + abs(heights[i] - heights[i-2]); 
//         }

//         return dp[i] = min(left, right);
//     }   


// Tabulation
// public:
//     int frogJump(vector<int>& heights) {
//         int n = heights.size();
//         vector<int> dp(n, 0);

//         dp[0] = 0;

//         for(int i = 1; i < n; i++) {
//             int jumpOne = dp[i-1] + abs(heights[i] - heights[i-1]);

//             int jumpTwo = INT_MAX;
//             if(i > 1) {
//                 jumpTwo = dp[i-2] + abs(heights[i] - heights[i-2]);
//             }
//             dp[i] = min(jumpOne, jumpTwo);
//         }
//         return dp[n-1];
//     }

// Space Optimization O(1)
public:
    int frogJump(vector<int>& heights) {
        int n = heights.size();
        if(n == 1) return 0;

        int prev2 = 0;
        int prev1 = abs(heights[1] - heights[0]);

        if(n == 2) return prev1;

        for(int i = 2; i < n; i++) {
            int jumpOne = prev1 + abs(heights[i] - heights[i-1]);

            int jumpTwo = prev2 + abs(heights[i] - heights[i-2]);
            
            int curr = min(jumpOne, jumpTwo);

            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};


int main() {
    Solution sol;
    vector<int> heights = {7, 5, 1, 2, 6};
    int final = sol.frogJump(heights);

    cout << final << endl;
}