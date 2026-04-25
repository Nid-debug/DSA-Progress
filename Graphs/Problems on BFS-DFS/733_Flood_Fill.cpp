/*
===========================================================
🧩 Problem: Flood Fill
===========================================================

Given an image represented as a 2D grid, starting from (sr, sc),
replace all connected cells having the same original color with
a new color.

Connectivity: 4-directional (up, down, left, right)

-----------------------------------------------------------
💡 Intuition:
-----------------------------------------------------------
- Start from (sr, sc)
- Store original color
- Traverse all connected cells having same color
- Replace them with new color

Two approaches:
1. DFS (recursive)
2. BFS (queue)

-----------------------------------------------------------
⏱ Complexity:
-----------------------------------------------------------
DFS:
Time  : O(N × M)
Space : O(N × M) recursion stack (worst case)

BFS:
Time  : O(N × M)
Space : O(N × M) queue
===========================================================
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ================= DFS Solution =================
class SolutionDFS {
public:
    void dfs(vector<vector<int>>& image, int row, int col, int color, int originalColor) {
        int n = image.size();
        int m = image[0].size();

        // Base case: out of bounds or different color
        if (row < 0 || col < 0 || row >= n || col >= m || image[row][col] != originalColor) return;

        // Fill color
        image[row][col] = color;

        // Explore all 4 directions
        dfs(image, row + 1, col, color, originalColor);
        dfs(image, row - 1, col, color, originalColor);
        dfs(image, row, col + 1, color, originalColor);
        dfs(image, row, col - 1, color, originalColor);
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];

        // Edge case: already same color
        if (originalColor == color) return image;

        dfs(image, sr, sc, color, originalColor);
        return image;
    }
};

// ================= BFS Solution =================
class SolutionBFS {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int origColor = image[sr][sc];

        // Edge case
        if (origColor == newColor) return image;

        int n = image.size(), m = image[0].size();

        vector<pair<int,int>> dirs = {
            {-1,0}, {0,1}, {1,0}, {0,-1}
        };

        queue<pair<int,int>> q;
        q.push({sr, sc});
        image[sr][sc] = newColor;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (auto [dr, dc] : dirs) {
                int nr = r + dr;
                int nc = c + dc;

                if (nr >= 0 && nc >= 0 && nr < n && nc < m && image[nr][nc] == origColor) {
                    image[nr][nc] = newColor;
                    q.push({nr, nc});
                }
            }
        }
        return image;
    }
};