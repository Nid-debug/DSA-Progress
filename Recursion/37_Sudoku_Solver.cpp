#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }

private:
    bool solve(vector<vector<char>>& board) {
        for(int row = 0; row < 9; row++) {
            for(int col = 0; col < 9; col++) {
                if(board[row][col] == '.') {
                    for(char num = '1'; num <= '9'; num++) {
                        if(isValid(board, row, col, num)) {
                            board[row][col] = num;
                            if(solve(board)) {
                                return true;
                            }
                            board[row][col] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool isValid(vector<vector<char>>& board, int row, int col, char num) {
        for(int i = 0; i < 9; i++) {
            if(board[row][i] == num) return false;
            if(board[i][col] == num) return false;
        }
            
        int boxRow = (row / 3) * 3;
        int boxCol = (col / 3) * 3;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[boxRow + i][boxCol + j] == num) {
                    return false;
                }
            }
        }
        return true;
    }
};
