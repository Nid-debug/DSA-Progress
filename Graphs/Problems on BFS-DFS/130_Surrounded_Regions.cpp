/*
-----------------------------------------
🧱 Surrounded Regions
-----------------------------------------

Approach:
- DFS from boundary 'O's
- Mark all boundary-connected 'O' as safe ('S')
- Flip remaining 'O' → 'X'
- Convert 'S' back → 'O'

Time Complexity:
- O(N * M)

Space Complexity:
- O(N * M) (recursion stack in worst case)
-----------------------------------------
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void dfs(int i, int j, vector<vector<char>>& board, int n, int m) {
        if(i < 0 || j < 0 || i >= n || j >= m || board[i][j] != 'O') return;

        board[i][j] = 'S'; // mark as safe

        dfs(i-1, j, board, n, m);
        dfs(i, j+1, board, n, m);
        dfs(i+1, j, board, n, m);
        dfs(i, j-1, board, n, m);
    }

    void solve(vector<vector<char>>& board) {
        int n = board.size(), m = board[0].size();

        // step 1: mark all border-connected O's as safe
        for(int i = 0; i < n; i++) {
            if(board[i][0] == 'O') dfs(i, 0, board, n, m);       // left col
            if(board[i][m-1] == 'O') dfs(i, m-1, board, n, m);   // right col
        }
        for(int j = 0; j < m; j++) {
            if(board[0][j] == 'O') dfs(0, j, board, n, m);        // top row
            if(board[n-1][j] == 'O') dfs(n-1, j, board, n, m);   // bottom row
        }

        // step 2 & 3: flip O -> X (surrounded) and S -> O (safe)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] == 'O') board[i][j] = 'X';
                else if(board[i][j] == 'S') board[i][j] = 'O';
            }
        }
    }
};
