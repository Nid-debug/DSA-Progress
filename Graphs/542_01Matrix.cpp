#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        int totalRows = mat.size();
        int totalCols = mat[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> distance(totalRows, vector<int>(totalCols, -1));

        // Step 1: Push all cells with 0 into the queue
        for (int row = 0; row < totalRows; row++)
        {
            for (int col = 0; col < totalCols; col++)
            {
                if (mat[row][col] == 0)
                {
                    distance[row][col] = 0;
                    q.push({row, col});
                }
            }
        }

        // Step 2: Perform BFS
        while (!q.empty())
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            // Move Down
            if (row + 1 < totalRows && distance[row + 1][col] == -1)
            {
                distance[row + 1][col] = distance[row][col] + 1;
                q.push({row + 1, col});
            }

            // Move Up
            if (row - 1 >= 0 && distance[row - 1][col] == -1)
            {
                distance[row - 1][col] = distance[row][col] + 1;
                q.push({row - 1, col});
            }

            // Move Right
            if (col + 1 < totalCols && distance[row][col + 1] == -1)
            {
                distance[row][col + 1] = distance[row][col] + 1;
                q.push({row, col + 1});
            }

            // Move Left
            if (col - 1 >= 0 && distance[row][col - 1] == -1)
            {
                distance[row][col - 1] = distance[row][col] + 1;
                q.push({row, col - 1});
            }
        }

        return distance;
    }
};

int main()
{
    Solution s;

    vector<vector<int>> mat = {
        {0, 0, 0},
        {0, 1, 0},
        {1, 1, 1}};

    vector<vector<int>> result = s.updateMatrix(mat);

    cout << "Updated Matrix:" << endl;
    for (const auto &row : result)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
