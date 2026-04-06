#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class SolutionMemo {
private:
    int solve(int r1, int c1, int c2, int m, vector<vector<int>>& grid, 
        vector<vector<vector<int>>>& dp) {

        if(c1 < 0 || c2 < 0 || c1 >= m || c2 >= m) return INT_MIN;

        if(r1 == grid.size()-1) {
            if(c1 == c2) return grid[r1][c1];
            else return grid[r1][c1] + grid[r1][c2];
        }

        if(dp[r1][c1][c2] != -1) return dp[r1][c1][c2];

        int maxi = INT_MIN;
        for(int i = -1; i <= +1; i++) {
            for(int j = -1; j <= +1; j++) {
                int value = 0;
                if(c1 == c2) value = grid[r1][c1];
                else value = grid[r1][c1] + grid[r1][c2];
                value += solve(r1+1, c1+i, c2+j, m, grid, dp);
                maxi = max(maxi, value);
            }
        }
        return dp[r1][c1][c2] = maxi;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
        return solve(0, 0, m-1, m, grid, dp);
    }
};

class SolutionTab {
public: 
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, 0)));

        for(int c1 = 0; c1 < m; c1++) {
            for(int c2 = 0; c2 < m; c2++) {
                if(c1 == c2) dp[n-1][c1][c2] = grid[n-1][c1];
                else dp[n-1][c1][c2] = grid[n-1][c1] + grid[n-1][c2];
            }
        }

        for(int row = n - 2; row >= 0; row--) {
            for(int c1 = 0; c1 < m; c1++) {
                for(int c2 = 0; c2 < m; c2++) {
                    int maxi = -1e9;

                    for(int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            int nc1 = c1 + i;
                            int nc2 = c2 + j;

                            if(nc1 >= 0 && nc1 < m && nc2 >= 0 && nc2 < m) {
                                int value = 0;

                                if(c1 == c2) value = grid[row][c1];
                                else value = grid[row][c1] + grid[row][c2];

                                value += dp[row + 1][nc1][nc2];
                                maxi = max(maxi, value);
                            }
                        }
                    }
                    dp[row][c1][c2] = maxi;
                }
            }
        }
        return dp[0][0][m-1];
    }
};

class SolutionSpaceOpti {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        // dp[row][c1][c2]
        vector<vector<vector<int>>> front(n, vector<vector<int>>(m, vector<int>(m, 0)));

        // 1. Base Case: Fill the last row
        for (int c1 = 0; c1 < m; c1++) {
            for (int c2 = 0; c2 < m; c2++) {
                if (c1 == c2) front[n - 1][c1][c2] = grid[n - 1][c1];
                else front[n - 1][c1][c2] = grid[n - 1][c1] + grid[n - 1][c2];
            }
        }

        // 2. Fill the DP table from bottom to top
        for (int row = n - 2; row >= 0; row--) {
            for (int c1 = 0; c1 < m; c1++) {
                for (int c2 = 0; c2 < m; c2++) {
                    
                    int curr = -1e9;
                    // Calculate cherries picked at current row once
                    int cherries = (c1 == c2) ? grid[row][c1] : grid[row][c1] + grid[row][c2];

                    // Inner 9-way movement loops
                    for (int i = -1; i <= 1; i++) {
                        for (int j = -1; j <= 1; j++) {
                            // Boundary check using inline math
                            if (c1 + i >= 0 && c1 + i < m && c2 + j >= 0 && c2 + j < m) {
                                curr = max(curr, cherries + front[row + 1][c1 + i][c2 + j]);
                            }
                        }
                    }
                    front[row][c1][c2] = curr;
                }
            }
        }
        // 3. Final answer starts from Row 0, Robot 1 at Col 0, Robot 2 at Col m-1
        return front[0][0][m - 1];
    }
};


int main() {
    SolutionMemo sol;
    SolutionTab tab;
    SolutionSpaceOpti spa;
    vector<vector<int>> grid = {{3,1,1},{2,5,1},{1,5,5},{2,1,1}};
    cout << sol.cherryPickup(grid) << endl;
    cout << tab.cherryPickup(grid) << endl;
    cout << spa.cherryPickup(grid) << endl;
}