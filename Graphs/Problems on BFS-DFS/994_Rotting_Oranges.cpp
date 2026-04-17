/*
-----------------------------------------
🍊 Rotten Oranges (Multi-Source BFS)
-----------------------------------------

Approach:
- Multi-source BFS
- Push all rotten oranges initially
- Spread rot level by level (minute by minute)

Time Complexity:
- O(N * M)

Space Complexity:
- O(N * M) (queue in worst case)
-----------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int fresh = 0;
        int minutes = 0;

        queue<pair<int, int>> q;

        vector<pair<int, int>> dirs = {
            {-1, 0}, {0, 1}, {1, 0}, {0, -1}
        };

        // Step 1: Initialize queue and count fresh oranges
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) q.push({i, j});
                if (grid[i][j] == 1) fresh++;
            }
        }

        // Step 2: BFS traversal
        while (!q.empty() && fresh > 0) {
            int size = q.size();
            minutes++;

            for (int k = 0; k < size; k++) {
                auto [r, c] = q.front();
                q.pop();

                for (auto [dr, dc] : dirs) {
                    int nr = r + dr;
                    int nc = c + dc;

                    if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;
                        fresh--;

                        q.push({nr, nc});
                    }
                }
            }
        }
        return (fresh == 0) ? minutes : -1;
    }
};