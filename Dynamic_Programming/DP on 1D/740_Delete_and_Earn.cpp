/*
💰 Problem: Delete and Earn

You are given an integer array nums.

When you choose a number nums[i]:
- You earn nums[i] points.
- Every occurrence of nums[i] is removed.
- Every occurrence of nums[i] - 1 is also removed.
- Every occurrence of nums[i] + 1 is also removed.

Goal:
Return the maximum number of points you can earn.

-----------------------------------------------------

💡 Key Transformation:

Instead of thinking about individual elements,
convert the problem into a House Robber problem.

For every value x: points[x] = x × frequency of x

Example:

nums = [2, 2, 3, 3, 3, 4]

points:

2 → 4
3 → 9
4 → 4

Now: Choosing 3 means we cannot choose 2 or 4.

So the problem becomes:
    Choose maximum points from an array
    where adjacent values cannot both be chosen.

This is exactly the House Robber pattern.

-----------------------------------------------------

🧠 Memoization (Top-Down):

At index i:

1. Skip value i: solve(i - 1)

2. Take value i: points[i] + solve(i - 2)

3. Take maximum: dp[i] = max(skip, take)

-----------------------------------------------------

🧠 Tabulation (Bottom-Up):

1. Build the points array.

2. Define: dp[i] = maximum points using values 0...i

3. Transition:
       skip = dp[i - 1]
       take = points[i] + dp[i - 2]
       dp[i] = max(skip, take)

-----------------------------------------------------

🧠 Space Optimized:

Only the previous two DP states are required:
    prev2 = dp[i - 2]
    prev1 = dp[i - 1]

For every i: current = max(prev1, prev2 + points[i])

Then shift:
    prev2 = prev1
    prev1 = current

-----------------------------------------------------

⏱ Time Complexity:

Let M = maximum value in nums.

Building points: O(N)

DP: O(M)

Total: O(N + M)

-----------------------------------------------------

📦 Space Complexity:

Memoization: O(M) → points + dp + recursion stack

Tabulation: O(M) → points + dp

Space Optimized: O(M) → points array only

-----------------------------------------------------
*/

#include <iostream>
#include <vector>
using namespace std;

class SolutionMemo {
public:
    int solve(int i, vector<int>& points, vector<int>& dp) {
        if(i < 0) return 0;

        if(dp[i] != -1) return dp[i];

        int skip = solve(i - 1, points, dp);
        int take = points[i] + solve(i - 2, points, dp);

        return dp[i] = max(skip, take);
    }
 
    int deleteAndEarn(vector<int>& nums) {
        int maxVal = 0;
        for(int num : nums) maxVal = max(maxVal, num);

        vector<int> points(maxVal + 1, 0);
        for(int num : nums) points[num] += num;

        vector<int> dp(maxVal + 1, -1);
        return solve(maxVal, points, dp);
    }
};

class SolutionTab {
public:
    int deleteAndEarn(vector<int>& nums) {
        if(nums.empty()) return 0;

        int maxVal = 0;
        for(int num : nums) maxVal = max(maxVal, num);

        vector<int> points(maxVal + 1, 0);
        for(int num : nums) points[num] += num;

        vector<int> dp(maxVal + 1, 0);
        dp[0] = points[0];

        if(maxVal >= 1) {
            dp[1] = max(points[0], points[1]);
        }

        for(int i = 2; i <= maxVal; i++) {
            int skip = dp[i - 1];
            int take = points[i] + dp[i - 2];
            dp[i] = max(skip, take);
        }

        return dp[maxVal];
    }
};

class SolutionSpace {
public:
    int deleteAndEarn(vector<int>& nums) {
        if(nums.empty()) return 0;

        int maxVal = 0;
        for(int num : nums) maxVal = max(maxVal, num);

        vector<int> points(maxVal + 1, 0);
        for(int num : nums) points[num] += num;

        int prev2 = 0;
        int prev1 = 0;

        for(int i = 0; i <= maxVal; i++) {
            int current = max(prev1, prev2 + points[i]);
            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }
};