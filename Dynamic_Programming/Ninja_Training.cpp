#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    int solve(int day, int lastTask, vector<vector<int>>& points, vector<vector<int>>& dp) {
        // Base Case: On day 0, we simply pick the best task 
        // that isn't the one we did on day 1.
        if (day == 0) {
            int maxi = 0;
            for (int task = 0; task <= 2; task++) {
                if (task != lastTask) {
                    maxi = max(maxi, points[0][task]);
                }
            }
            return maxi;
        }

        if (dp[day][lastTask] != -1) return dp[day][lastTask];

        int maxi = 0;
        // Try all 3 tasks for the current day
        for (int task = 0; task <= 2; task++) {
            // Rule: Current task cannot be the same as the lastTask
            if (task != lastTask) {
                // Point = points for current task + best points from previous days
                int point = points[day][task] + solve(day - 1, task, points, dp);
                maxi = max(maxi, point);
            }
        }

        return dp[day][lastTask] = maxi;
    }

public:
    int ninjaTraining(int n, vector<vector<int>>& points) {
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solve(n - 1, 3, points, dp);
    }
};
