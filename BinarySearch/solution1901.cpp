class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int left = 0, right = n - 1;

        while (left <= right) {
            int midCol = left + (right - left) / 2;

            int maxRow = 0;
            for (int row = 1; row < m; row++) {
                if (mat[row][midCol] > mat[maxRow][midCol]) {
                    maxRow = row;
                }
            }

            int midVal = mat[maxRow][midCol];

            int leftNeighbor  = (midCol - 1 >= 0)     ? mat[maxRow][midCol - 1] : -1;
            int rightNeighbor = (midCol + 1 < n) ? mat[maxRow][midCol + 1] : -1;

            if (midVal > leftNeighbor && midVal > rightNeighbor) {
                return {maxRow, midCol};
            } else if (leftNeighbor > midVal) {
                right = midCol - 1; 
            } else {
                left = midCol + 1; 
            }
        }
        return {-1, -1}; 
    }
};
