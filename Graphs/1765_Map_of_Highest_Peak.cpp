#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int m = isWater.size();
        int n = isWater[0].size();

        queue<pair<int, int>> q;
        vector<vector<int>> height(m, vector<int>(n, -1));
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(isWater[i][j] == 1) {
                    height[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        
        while(!q.empty()) {
            auto current = q.front();
            int x = current.first;
            int y = current.second;
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if (nx >= 0 && ny >= 0 && nx < m && ny < n && height[nx][ny] == -1) {
                    height[nx][ny] = height[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return height;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> isWater = {
        {0,0,1},
        {1,0,0},
        {0,0,0}
    };

    vector<vector<int>> result = sol.highestPeak(isWater);
    
    cout << "Highest Peak Grid:" << endl;
    for (const auto& row : result) {
        for (int h : row) {
            cout << h << " ";
        }
        cout << endl;
    }
    return 0;
}