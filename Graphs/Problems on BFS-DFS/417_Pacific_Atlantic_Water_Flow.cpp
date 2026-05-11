/*
🌊 Problem: Pacific Atlantic Water Flow

You are given an m x n grid of heights.

Water can flow from a cell to its neighboring cell (up, down, left, right)
IF the neighbor's height is <= current cell.

Two oceans:
- Pacific → touches top row and left column
- Atlantic → touches bottom row and right column

Goal:
Return all cells from which water can flow to BOTH oceans.

-----------------------------------------------------

💡 Approach:

👉 Key Idea (IMPORTANT):
Instead of flowing water from each cell → oceans ❌ (expensive)

We REVERSE the flow:
- Start from oceans
- Move "uphill" (to cells with >= height)

So:
- Run BFS/DFS from Pacific borders
- Run BFS/DFS from Atlantic borders
- Find intersection

-----------------------------------------------------

🧠 BFS Approach:

1. Initialize two visited matrices:
   - pacific[][] 
   - atlantic[][]

2. Push all boundary cells into queues:
   - Pacific → top row + left col
   - Atlantic → bottom row + right col

3. Run BFS:
   - Move only to cells with height >= current (reverse flow)

4. Cells reachable in BOTH → answer

-----------------------------------------------------

🧠 DFS Approach:

1. Same idea, but use DFS instead of BFS

2. Start DFS from:
   - Pacific borders
   - Atlantic borders

3. Mark reachable cells

4. Take intersection

-----------------------------------------------------

⚠️ Key Insight:
- Reverse thinking avoids redundant work
- Each cell is visited at most once per ocean

-----------------------------------------------------

⏱ Time Complexity:
- O(N × M)

📦 Space Complexity:
- BFS: O(N × M) (queue + visited arrays)
- DFS: O(N × M) (recursion stack + visited)
*/

#include <vector>
#include <queue>    
using namespace std;

class SolutionBFS {
public:
    int m, n;
    vector<pair<int,int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

    void bfs(vector<vector<int>>& heights, vector<vector<bool>>& vis, queue<pair<int,int>>& q) {
        while(!q.empty()) {
            auto [r, c] = q.front(); q.pop();

            for(auto [dr, dc] : dirs) {
                int nr = r+dr, nc = c+dc;
                if(nr >= 0 && nr < m && nc >= 0 && nc < n && !vis[nr][nc]
                   && heights[nr][nc] >= heights[r][c]) { // reverse flow — go uphill!
                    vis[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        m = heights.size(), n = heights[0].size();

        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        queue<pair<int,int>> pacificQ, atlanticQ;

        // pacific touches top row and left col
        // atlantic touches bottom row and right col
        for(int i = 0; i < m; i++) {
            pacific[i][0] = true;
            pacificQ.push({i, 0});
            atlantic[i][n-1] = true;
            atlanticQ.push({i, n-1});
        }
        for(int j = 0; j < n; j++) {
            pacific[0][j] = true;
            pacificQ.push({0, j});
            atlantic[m-1][j] = true;
            atlanticQ.push({m-1, j});
        }

        // BFS from both oceans
        bfs(heights, pacific, pacificQ);
        bfs(heights, atlantic, atlanticQ);

        // cells reachable from both = answer
        vector<vector<int>> result;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(pacific[i][j] && atlantic[i][j])
                    result.push_back({i, j});

        return result;
    }
};

class SolutionDFS {
public:
    int m, n;
    vector<pair<int,int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

    void dfs(int i, int j, vector<vector<int>>& heights, vector<vector<bool>>& vis) {
        vis[i][j] = true;

            for(auto [dr, dc] : dirs) {
                int nr = i+dr, nc = j+dc;

                if(nr >= 0 && nr < m && nc >= 0 && nc < n && !vis[nr][nc]
                   && heights[nr][nc] >= heights[i][j]) { // reverse flow — go uphill!
                    dfs(nr, nc, heights, vis);
                }
            }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        m = heights.size(), n = heights[0].size();

        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        // pacific touches top row and left col
        // atlantic touches bottom row and right col
        for(int i = 0; i < m; i++) {
            dfs(i, 0, heights, pacific);
            dfs(i, n-1, heights, atlantic);
        }
        for(int j = 0; j < n; j++) {
            dfs(0, j, heights, pacific);
            dfs(m-1, j, heights, atlantic);
        }

        // cells reachable from both = answer
        vector<vector<int>> result;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }
};
