/*
-----------------------------------------
🌐 Number of Provinces
-----------------------------------------

Approach:
- Treat matrix as graph (adjacency matrix)
- Use DFS to count connected components

Time Complexity:
- O(N^2)

Space Complexity:
- O(N) (visited array + recursion stack)
-----------------------------------------
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void dfs(int node, vector<bool>& vis, vector<vector<int>>& isConnected, int n) {
        vis[node] = true;

        for (int j = 0; j < n; j++) {
            if (isConnected[node][j] == 1 && !vis[j]) {
                dfs(j, vis, isConnected, n);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int province = 0;

        vector<bool> vis(n, false);

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, vis, isConnected, n);
                province++;
            }
        }
        return province;
    }
};