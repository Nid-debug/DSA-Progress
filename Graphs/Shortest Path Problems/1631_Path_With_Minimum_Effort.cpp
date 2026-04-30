/*
===========================================================
LC-1631 Problem : Path With Minimum Effort
===========================================================

Given a 2D grid heights, find a path from (0,0) to (n-1,m-1)
such that the maximum absolute difference between adjacent
cells in the path is minimized.

👉 Effort of a path = max(|height difference| along the path)

Return the minimum effort required.

-----------------------------------------------------------
💡 Intuition:
-----------------------------------------------------------
- This is NOT normal shortest path (sum of weights)
- Instead, we minimize the "maximum edge weight" in the path

👉 Classic Dijkstra variation:
- Instead of sum → take max

Steps:
1. Use a min-heap (priority queue)
2. Store {effort, row, col}
3. For each move:
   newEffort = max(currentEffort, abs(height difference))
4. Relax only if newEffort is smaller

-----------------------------------------------------------
🔁 Why Dijkstra works?
-----------------------------------------------------------
- Greedy: always expand the path with minimum effort so far
- Once we reach destination → it's optimal

-----------------------------------------------------------
⏱ Complexity:
-----------------------------------------------------------
Time  : O(N × M × log(N × M))
Space : O(N × M)
===========================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist[0][0] = 0;

        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        pq.push({0, 0, 0}); // {effort, row, col}

        while(!pq.empty()) {
            auto [effort, row, col] = pq.top(); pq.pop();

            if(row == n-1 && col == m-1) return effort; // reached destination

            if(effort > dist[row][col]) continue;

            for(auto [dr, dc] : dirs) {
                int newRow = row + dr;
                int newCol = col + dc;

                if(newRow >= 0 && newRow < n && newCol >= 0 && newCol < m) {
                    int newEffort = max(effort, abs(heights[newRow][newCol] - heights[row][col]));

                    if(newEffort < dist[newRow][newCol]) {
                        dist[newRow][newCol] = newEffort;
                        pq.push({newEffort, newRow, newCol});
                    }
                }
            }
        }
        return 0; // should never reach here since there's always a path from (0,0) to (n-1,m-1)
    }
};