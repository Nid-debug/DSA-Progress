/*
    🏝️ Number of Enclaves

    🔹 Problem:
    Given a grid of 0s (water) and 1s (land),
    return the number of land cells from which we cannot walk off the boundary.

    🔹 Idea:
    - Any land connected to boundary is NOT an enclave
    - So:
        1. Run DFS from boundary cells
        2. Mark all reachable land as visited (2)
        3. Count remaining 1s → these are enclaves

    🔹 Time Complexity: O(N * M)
    🔹 Space Complexity: O(N * M) (recursion stack in worst case)
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void dfs(int i, int j, vector<vector<int>>& grid, int n, int m) {
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != 1) return;

        grid[i][j] = 2; // mark as visited (safe)

        // explore all 4 directions
        dfs(i - 1, j, grid, n, m);
        dfs(i, j + 1, grid, n, m);
        dfs(i + 1, j, grid, n, m);
        dfs(i, j - 1, grid, n, m);
    }

    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // left & right boundary
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1) dfs(i, 0, grid, n, m);
            if (grid[i][m - 1] == 1) dfs(i, m - 1, grid, n, m);
        }

        // top & bottom boundary
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1) dfs(0, j, grid, n, m);
            if (grid[n - 1][j] == 1) dfs(n - 1, j, grid, n, m);
        }

        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) count++;
            }
        }
        return count;
    }
};