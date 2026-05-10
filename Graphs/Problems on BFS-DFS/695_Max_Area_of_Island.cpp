/*
🏝️ Problem: Max Area of Island

You are given a 2D grid of 0s and 1s:
- 1 → land
- 0 → water

Goal:
Find the maximum area of an island.

An island is formed by connecting adjacent lands (4 directions).

-----------------------------------------------------

💡 Approach:

👉 Idea:
- Traverse the grid
- Whenever you find a '1', explore the full island
- Count its size
- Keep track of maximum area

-----------------------------------------------------

🧠 BFS Approach:

1. For every cell:
   - If it's land (1):
       → Start BFS
       → Mark visited by converting to 0

2. Use queue:
   - Expand in 4 directions
   - Count number of cells visited

3. Update maxArea

-----------------------------------------------------

🧠 DFS Approach:

1. For every cell:
   - If it's land and not visited:
       → Run DFS

2. DFS:
   - Visit all connected land cells
   - Return total area

3. Track maximum area

-----------------------------------------------------

⚠️ Key Insight:
- Each island is explored exactly once
- BFS modifies grid directly
- DFS uses visited array

-----------------------------------------------------

⏱ Time Complexity:
- O(N × M)

📦 Space Complexity:
- BFS: O(N × M) (queue in worst case)
- DFS: O(N × M) (recursion stack + visited)
*/

#include <vector>
#include <queue>
using namespace std;

class SolutionBFS {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int maxArea = 0;

        vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) {
                    int currentArea = 0;
                    queue<pair<int, int>> q;

                    q.push({i, j});
                    grid[i][j] = 0;

                    while(!q.empty()) {
                        auto [r, c] = q.front();
                        q.pop();
                        currentArea++;

                        for(auto [dr, dc] : dirs) {
                            int nr = r + dr;
                            int nc = c + dc;

                            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1) {
                                q.push({nr, nc});
                                grid[nr][nc] = 0; 
                            }
                        }
                    }
                    maxArea = max(maxArea, currentArea);
                }
            }
        }
        return maxArea;
    }
};

class SolutionDFS {
public:
    int dfs(int i, int j, vector<vector<int>>& vis, vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vis[i][j] = 1;

        vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        int area = 1;
            for(auto [row, col] : dirs) {
                int newRow = i + row;
                int newCol = j + col;

                if(newRow < n && newRow >= 0 && newCol < m && newCol >= 0 
                && grid[newRow][newCol] == 1 && !vis[newRow][newCol]) {
                    area += dfs(newRow, newCol, vis, grid);
                }
            }
            return area;
        }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int maxArea = 0;

        vector<vector<int>> vis(n, vector<int>(m, 0));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1 && !vis[i][j]) {
                    maxArea = max(maxArea, dfs(i, j, vis, grid));
                }
            }
        }
        return maxArea;
    }
};