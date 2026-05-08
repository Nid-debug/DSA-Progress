#include <vector>
#include <queue>
using namespace std;    

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {

        int n = grid.size();

        vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        pq.push({grid[0][0], {0, 0}});
        
        visited[0][0] = true;

        while(!pq.empty()) {
            auto [height, pos] = pq.top(); pq.pop();
            int row = pos.first;
            int col = pos.second;
            
            if(row == n - 1 && col == n - 1) return height;
            
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