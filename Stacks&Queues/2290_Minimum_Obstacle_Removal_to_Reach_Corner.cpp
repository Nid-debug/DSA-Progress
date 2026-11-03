#include <vector>
#include <deque>
#include <climits>
using namespace std;

/*
🧱 LeetCode 2290: Minimum Obstacle Removal to Reach Corner

Problem:
You are given an m x n grid where:
- grid[r][c] == 0 means the cell is empty.
- grid[r][c] == 1 means the cell contains an obstacle.

You can move up, down, left, or right.
Return the minimum number of obstacles that must be removed
to travel from the top-left cell (0, 0) to the bottom-right
cell (m - 1, n - 1).

Approach: 0-1 BFS using a Deque

Intuition:
This problem can be treated as a shortest-path problem.

Each cell is a node, and moving to an adjacent cell has a cost:
- Cost 0 if the destination cell is empty.
- Cost 1 if the destination cell contains an obstacle.

Since edge weights are only 0 or 1, we can use 0-1 BFS
instead of Dijkstra's algorithm.

We maintain:
- dist[r][c]: Minimum obstacles removed to reach cell (r, c).
- deque: Stores cells that need to be processed.

Key Idea:
- If the next cell has weight 0, push it to the FRONT.
- If the next cell has weight 1, push it to the BACK.
- Update a cell only when we find a smaller distance.

Algorithm:
1. Initialize every distance to INT_MAX.
2. Set dist[0][0] = 0 and push (0, 0) into the deque.
3. While the deque is not empty:
   a. Remove the front cell.
   b. If it is the destination, return its distance.
   c. Explore all four neighboring cells.
   d. Calculate the cost of entering each neighbor.
   e. If a shorter path is found, update its distance.
   f. Push the neighbor to the front for cost 0,
      or to the back for cost 1.
4. Return the destination distance if the loop finishes.

Why 0-1 BFS?
Ordinary BFS works when all edges have equal weights.
Dijkstra works for general non-negative edge weights.
Here, every edge has weight 0 or 1, so a deque lets us
prioritize zero-cost moves efficiently.

Time Complexity: O(m * n)
Each cell has at most four neighbors, and 0-1 BFS runs
in linear time for graphs with edge weights 0 or 1.

Space Complexity: O(m * n)
The distance matrix and deque can each store O(m * n) cells.

Pattern to Remember:
Shortest Path + Edge Weights {0, 1} -> 0-1 BFS + Deque
*/

class Solution
{
public:
    int minimumObstacles(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

        deque<pair<int, int>> dq;

        dist[0][0] = 0;
        dq.push_back({0, 0});

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!dq.empty())
        {
            auto [r, c] = dq.front();
            dq.pop_front();

            if (r == m - 1 && c == n - 1)
                return dist[r][c];

            for (auto [dr, dc] : directions)
            {
                int nr = r + dr;
                int nc = c + dc;

                if (nr >= 0 && nr < m && nc >= 0 && nc < n)
                {
                    int weight = grid[nr][nc];

                    if (dist[r][c] + weight < dist[nr][nc])
                    {
                        dist[nr][nc] = dist[r][c] + weight;

                        if (weight == 0)
                        {
                            dq.push_front({nr, nc});
                        }
                        else
                        {
                            dq.push_back({nr, nc});
                        }
                    }
                }
            }
        }
        return dist[m - 1][n - 1];
    }
};