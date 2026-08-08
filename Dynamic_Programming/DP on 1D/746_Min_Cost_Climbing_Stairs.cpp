/*
🪜 Problem: Min Cost Climbing Stairs

You are given an integer array cost where:

    cost[i] = cost of stepping on stair i

You can start from either:
    - stair 0
    - stair 1

From each stair, you can climb:
    - 1 step
    - 2 steps

You can reach the top without paying for it.

Goal: Return the minimum cost required to reach the top.

-----------------------------------------------------

💡 Key Idea:

Think of the problem as:
"What is the minimum cost to reach each stair?"

At stair i, we can arrive from:
    i - 1
    i - 2

Therefore:
    dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])

-----------------------------------------------------

🧠 Memoization (Top-Down):

Define: solve(i) = minimum cost to reach the top starting from stair i

From stair i, we have two choices:

1. Take 1 step: cost[i] + solve(i + 1)

2. Take 2 steps: cost[i] + solve(i + 2)

Take the minimum: dp[i] = min(step1, step2)

Base Case: i >= n → reached the top

Since we can start at either stair 0 or stair 1: 
answer = min(solve(0), solve(1))

-----------------------------------------------------

🧠 Tabulation (Bottom-Up):

Define: dp[i] = minimum cost to reach stair i

The top is represented by index n.

Starting position:
    dp[0] = 0
    dp[1] = 0

For every i >= 2: dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])

Answer: dp[n]

-----------------------------------------------------

🧠 Space Optimized:

For calculating dp[i], we only need:
    dp[i - 1]
    dp[i - 2]

So instead of storing the entire DP array:
    prev2 = dp[i - 2]
    prev1 = dp[i - 1]

Calculate: current = min(prev1 + cost[i - 1], prev2 + cost[i - 2])

Then shift:
    prev2 = prev1
    prev1 = current

-----------------------------------------------------

⚠️ Key Insight:

The top is NOT an actual stair.

If n = cost.size(): dp[n] = minimum cost to reach beyond the last stair.

That's why the answer is dp[n].

-----------------------------------------------------

⏱ Time Complexity:

Memoization: O(N)

Tabulation: O(N)

Space Optimized:
    O(N) → cost array
    O(1) → extra DP space

-----------------------------------------------------

📦 Space Complexity:

Memoization: O(N) → DP + recursion stack

Tabulation: O(N) → DP array

Space Optimized: O(1) → only two DP variables

-----------------------------------------------------

🧠 Revision Trigger:

Whenever you see:

- 1 or 2 steps allowed
- Minimum/maximum cost
- Current state depends on previous 1-2 states

Think: dp[i] = best(dp[i-1], dp[i-2])

*/

#include <vector>
using namespace std;

class SolutionMemo {
public: 
    int solve(int i, vector<int>& cost, vector<int>& dp) {
        if(i >= cost.size()) return 0;

        if(dp[i] != -1) return dp[i];

        int step1 = cost[i] + solve(i + 1, cost, dp);
        int step2 = cost[i] + solve(i + 2, cost, dp);

        return dp[i] = min(step1, step2);
    }
    
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n, -1);

        return min(solve(0, cost, dp), solve(1, cost, dp));
    }
};

class SolutionTab {
public: 
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1, 0);

        dp[0] = 0;
        dp[1] = 0;

        for(int i = 2; i <= n; i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }

        return dp[n];
    }
};

class SolutionSpace {
public: 
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();

        int prev2 = 0;
        int prev1 = 0;

        for(int i = 2; i <= n; i++) {
            int current = min(prev1 + cost[i - 1], prev2 + cost[i - 2]);
            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }
};