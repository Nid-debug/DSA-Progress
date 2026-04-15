# 🧠 Dynamic Programming (DP) Mastery

This repository documents my journey of rebuilding my DP intuition after realizing I was relying too much on patterns without understanding state transitions.

## 🛠 My Problem-Solving Workflow

For every challenge, I follow a systematic approach:

1. **State Definition:** Clearly defining what each DP state represents.
2. **Recursive (Brute Force):** Identifying base cases and recurrence relations.
3. **Memoization (Top-Down):** Optimizing recursion using caching.
4. **Tabulation (Bottom-Up):** Converting to iterative DP.
5. **Space Optimization:** Reducing space complexity wherever possible.
6. **Complexity Analysis:** Evaluating time and space trade-offs.

## 📂 Pattern Categorization

### 📏 [DP on 1D Arrays]

- Linear transitions and space optimization.
- Core Idea: Solving the current step using the results of n-1 or n-2 previous steps.

### 🗺️ [DP on Grids]

- Fixed and variable start/end problems
- Pathfinding with min/max cost

### 🧵 [DP on Strings & Subsequences]

- LCS, Edit Distance, String Matching
- Subset Sum & Partition problems

### 📈 [DP on Stocks]

Comprehensive solutions for the LeetCode Stock series:

- Best Time to Buy/Sell I & II
- Best Time to Buy/Sell III & IV (k transactions)
- Cooldown & Transaction Fees (state machine approach)

### 🔢 [DP on LIS]

- LIS and its variations

### 🔢 [DP on MCM]

- Solving for ranges [i..j].
- Workflow: Identify the "last action" performed in the range to set up the recurrence.
- Problems: Matrix Multiplication, Palindromic Partitioning, Optimal Binary Search Tree.

---

“Dynamic Programming is not about memorizing solutions, but recognizing patterns and defining the right state.”
