#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> findPath(vector<vector<int>> &grid) {
        vector<string> ans;
        int n = grid.size();

        if (n == 0 || grid[0][0] == 0) return ans;

        string path = "";
        dfs(0, 0, grid, n, path, ans);
        return ans;
    }

private:
    void dfs(int i, int j, vector<vector<int>> &grid, int n,
             string &path, vector<string> &ans) {

        if (i == n - 1 && j == n - 1) {
            ans.push_back(path);
            return;
        }

        // mark visited
        grid[i][j] = 0;

        int di[] = {1, 0, 0, -1};
        int dj[] = {0, -1, 1, 0};
        char dir[] = {'D', 'L', 'R', 'U'};

        for (int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];

            if (ni >= 0 && nj >= 0 && ni < n && nj < n && grid[ni][nj] == 1) {
                path.push_back(dir[k]);
                dfs(ni, nj, grid, n, path, ans);
                path.pop_back();
            }
        }

        // backtrack (unmark)
        grid[i][j] = 1;
    }
};
