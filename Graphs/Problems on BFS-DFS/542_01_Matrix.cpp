/*
-----------------------------------------
🧮 01 Matrix (Distance to Nearest Zero)
-----------------------------------------

Approach:
- Multi-source BFS
- Push all 0s into queue initially
- Expand layer by layer to compute minimum distance

Time Complexity:
- O(N * M)

Space Complexity:
- O(N * M)
-----------------------------------------
*/

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        queue<pair<int,int>> q;
        vector<pair<int,int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(mat[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        while(!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for(auto [dr, dc] : dirs) {
                int nr = r+dr, nc = c+dc;
                if(nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == INT_MAX) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        return dist;
    }
};