/*
===========================================================
🧩 Problem: Shortest Path in Binary Matrix
===========================================================

Given an n x n binary matrix grid:
- 0 → empty cell (can move)
- 1 → blocked cell

Find the length of the shortest path from (0,0) to (n-1,n-1).

Rules:
- You can move in 8 directions (including diagonals)
- Path length = number of cells in the path
- Return -1 if no such path exists

-----------------------------------------------------------
💡 Intuition:
-----------------------------------------------------------
- This is a classic shortest path problem in an unweighted grid
- BFS guarantees shortest path

Steps:
1. Start from (0,0)
2. Explore all 8 directions
3. Mark visited cells (by converting 0 → 1)
4. Use level-order BFS → each level = +1 step
5. Stop when reaching (n-1, n-1)

-----------------------------------------------------------
⏱ Complexity:
-----------------------------------------------------------
Time  : O(N²)
Space : O(N²) (queue in worst case) 
===========================================================
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();

        // Edge cases
        if(grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;
        if(n == 1) return 1;

        vector<pair<int, int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

        queue<pair<int, int>> q;
        q.push({0, 0});
        grid[0][0] = 1;

        int steps = 1;

        while(!q.empty()) {
            int size = q.size();
            steps++;

            for(int i = 0; i < size; i++) {
                auto [row, col] = q.front(); q.pop();

                for(auto [dr, dc] : dirs) {
                    int newRow = row + dr;
                    int newCol = col + dc;

                    if(newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && grid[newRow][newCol] == 0) {
                        if(newRow == n-1 && newCol == n-1) return steps;

                        q.push({newRow, newCol});
                        grid[newRow][newCol] = 1;
                    }
                }
            }
        }
        return -1;
    }
};  