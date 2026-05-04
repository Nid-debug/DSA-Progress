/*
🔪 Problem: Palindrome Partitioning II

Given a string s,
partition it such that every substring is a palindrome.

Goal:
Return the minimum number of cuts needed.

-----------------------------------------------------

💡 Approach:

👉 Idea:
- Try every possible partition
- Only cut when substring is palindrome

-----------------------------------------------------

🧠 Memoization (Top-Down):

1. At index i:
   - Try all j from i → n-1
   - If s[i...j] is palindrome:
       cost = 1 + solve(j+1)

2. Take minimum over all choices

3. Final answer:
   dp[0] - 1  (because last partition doesn't need a cut)

-----------------------------------------------------

🧠 Tabulation (Bottom-Up):

1. dp[i] = minimum partitions needed from i → end

2. Fill from back:
   - For each i:
       try all j ≥ i
       if palindrome → dp[i] = min(1 + dp[j+1])

3. Answer = dp[0] - 1

-----------------------------------------------------

⚠️ Key Insight:
- We are minimizing number of partitions
- Cuts = partitions - 1

-----------------------------------------------------

⏱ Time Complexity:

Memoization:
- O(N³)
  (N² substrings * palindrome check O(N))

Tabulation:
- O(N³) same reason

-----------------------------------------------------

📦 Space Complexity:
- DP array: O(N)
- Recursion stack (memo): O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isPalindrome(int i, int j, string& s) {
        while(i < j) {
            if(s[i] != s[j]) return false;
            i++; 
            j--;
        }
        return true;
    }

    int solve(int i, int n, string& s, vector<int>& dp) {
        if(i == n) return 0;
        int minCost = 1e9;

        if(dp[i] != -1) return dp[i];

        for(int j = i; j < n; j++) {
            if(isPalindrome(i, j, s)) {
                int cost = 1 + solve(j+1, n, s, dp);
                minCost = min(minCost, cost);
            }
        }
        return dp[i] = minCost;
    }

    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return solve(0, n, s, dp) - 1;
    }
};

class SolutionTab {
public:
    bool isPalindrome(int i, int j, string& s) {
        while(i < j) {
            if(s[i] != s[j]) return false;
            i++; 
            j--;
        }
        return true;
    }

    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[n] = 0;

        for(int i = n-1; i >= 0; i--) {
            int minCost = 1e9;
            for(int j = i; j < n; j++) {
                if(isPalindrome(i, j, s)) {
                    int cost = 1 + dp[j+1];
                    minCost = min(minCost, cost);
                }
            }
            dp[i] = minCost;
        }
        return dp[0] - 1;
    }
};