#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        
        // Try starting from each cell
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == word[0]) {
                    if(dfs(board, word, i, j, 0)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int index) {
        // If we've matched all characters
        if(index == word.length()) {
            return true;
        }
        
        // Check boundaries
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
            return false;
        }
        
        // Check if current character matches
        if(board[i][j] != word[index]) {
            return false;
        }
        
        // Mark current cell as visited by temporarily changing it
        char temp = board[i][j];
        board[i][j] = '#';
        
        // Try all 4 directions
        bool found = dfs(board, word, i + 1, j, index + 1) ||  // down
                     dfs(board, word, i - 1, j, index + 1) ||  // up
                     dfs(board, word, i, j + 1, index + 1) ||  // right
                     dfs(board, word, i, j - 1, index + 1);    // left
        
        // Backtrack: restore the cell
        board[i][j] = temp;
        
        return found;
    }
};