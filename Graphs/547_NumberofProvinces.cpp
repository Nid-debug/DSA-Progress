#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void dfs(int node, vector<bool>& vis, vector<vector<int>>& isConnected, int n) {
        vis[node] = true;

        for(int j = 0; j < n; j++) {
            if(isConnected[node][j] == 1 && !vis[j]) {
                dfs(j, vis, isConnected, n);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int province = 0;
        vector<bool> vis(n, false);

        for(int i = 0; i < n; i++) {
            if(!vis[i]) {
                dfs(i, vis, isConnected, n);
                province++;
            }
        }

        return province;
    }
};

int main() {
    Solution s;

    vector<vector<int>> isConnected = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
    };

    int result = s.findCircleNum(isConnected);

    cout << "Total Number of Provinces are: " << result << endl; //3   
    return 0;
}