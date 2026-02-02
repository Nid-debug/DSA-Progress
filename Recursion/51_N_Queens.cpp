#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));

        backtrack(0, n, board, result);
        return result;
    }

private:
    void backtrack(int row, int n, vector<string>& board,
                   vector<vector<string>>& result) {
        // If all rows are filled, we found a valid board
        if (row == n) {
            result.push_back(board);
            return;
        }

        // Try placing a queen in every column of this row
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col, board, n)) {
                board[row][col] = 'Q';       // place queen
                backtrack(row + 1, n, board, result);
                board[row][col] = '.';       // remove queen (backtrack)
            }
        }
    }

    bool isSafe(int row, int col, vector<string>& board, int n) {
        // Check same column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q')
                return false;
        }

        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }

        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q')
                return false;
        }

        return true;
    }
};

int main() {
    Solution sol;
    int n = 4;

    vector<vector<string>> final = sol.solveNQueens(n);
    for (const auto& board : final) {
        for (const string& row : board) {
            cout << row << endl; 
        }
        cout << "----" << endl; 
    }
    return 0;
}