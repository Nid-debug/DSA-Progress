/*
    🏝️ Number of Islands (DFS + BFS)

    🔹 Problem:
    Given a 2D grid of '1's (land) and '0's (water),
    return the number of islands.

    An island is surrounded by water and is formed by
    connecting adjacent lands (4-directionally).

    🔹 Idea:
    - Traverse the grid
    - When we find unvisited land ('1'):
        → start DFS/BFS
        → mark entire connected component
        → increment island count

    🔹 Time Complexity: O(N * M)
    🔹 Space Complexity:
        DFS → O(N * M) (recursion stack)
        BFS → O(N * M) (queue)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class SolutionDFS {
public:
    // DFS to mark all connected land
    void dfs(int i, int j, vector<vector<bool>>& vis, vector<vector<char>>& grid, int n, int m) {

        // base case: out of bounds OR visited OR water
        if (i < 0 || j < 0 || i >= n || j >= m || vis[i][j] || grid[i][j] != '1') return;

        vis[i][j] = true;

        // explore all 4 directions
        dfs(i - 1, j, vis, grid, n, m);
        dfs(i, j + 1, vis, grid, n, m);
        dfs(i + 1, j, vis, grid, n, m);
        dfs(i, j - 1, vis, grid, n, m);
    }

    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int islands = 0;

        vector<vector<bool>> vis(n, vector<bool>(m, false));

        // traverse grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                // found new island
                if (grid[i][j] == '1' && !vis[i][j]) {
                    dfs(i, j, vis, grid, n, m);
                    islands++;
                }
            }
        }
        return islands;
    }
};

class SolutionBFS {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int count = 0;
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // traverse grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                // found new island
                if (grid[i][j] == '1') {
                    count++;

                    queue<pair<int, int>> q;
                    q.push({i, j});

                    // mark visited
                    grid[i][j] = '0';

                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();

                        for (auto dir : directions) {
                            int nx = x + dir.first;
                            int ny = y + dir.second;

                            if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == '1') {
                                q.push({nx, ny});
                                grid[nx][ny] = '0'; // mark visited
                            }
                        }
                    }
                }
            }
        }
        return count;
    }
};