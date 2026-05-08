/*
🏊 Problem: Swim in Rising Water

You are given an n x n grid where:
- grid[i][j] represents elevation

Water rises over time.

At time t:
You can enter cells with elevation <= t.

Goal:
Find the minimum time required to travel
from top-left (0,0) to bottom-right (n-1,n-1).

-----------------------------------------------------

💡 Key Observation:

The answer is determined by the
maximum elevation encountered along the path.

Example:
Path elevations:
0 → 1 → 5 → 2

Required time = 5

So:
We want a path minimizing the
maximum elevation.

-----------------------------------------------------

🧠 Approach: Dijkstra's Algorithm

👉 Idea:
- Treat each cell as a graph node
- Moving cost =
    max(current path height, next cell height)

Use Min Heap:
- Always process smallest possible height first

-----------------------------------------------------

🧠 Steps:

1. Start from (0,0)

2. Store in priority queue:
   {current max height, row, col}

3. Explore 4 directions

4. New path height:
   max(currentHeight, grid[newRow][newCol])

5. First time we reach destination
   gives minimum answer

-----------------------------------------------------

⚠️ Important Insight:

Unlike normal shortest path:
- We are NOT minimizing sum
- We are minimizing maximum elevation

-----------------------------------------------------

⏱ Time Complexity:
- O(N² log(N²))
- O(N² log N)

Reason:
- N² cells
- each heap operation takes log(N²)

-----------------------------------------------------

📦 Space Complexity:
- O(N²)
  visited array + priority queue
*/

#include <vector>
#include <queue>
using namespace std;    

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {

        int n = grid.size();

        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        // min heap: {height, {row, col}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        pq.push({grid[0][0], {0, 0}});

        visited[0][0] = true;

        while(!pq.empty()) {
            auto [height, pos] = pq.top(); pq.pop();
            int row = pos.first;
            int col = pos.second;
            
            if(row == n - 1 && col == n - 1) return height;
            
            // explore neighbours
            for(auto [dr, dc] : dirs) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if(newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && !visited[newRow][newCol]) {
                    pq.push({max(height, grid[newRow][newCol]), {newRow, newCol}});
                    visited[newRow][newCol] = true;
                }
            }
        }
        return -1;
    }
};