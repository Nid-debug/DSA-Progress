// LeetCode Problem 100: Same Tree
// Link: https://leetcode.com/problems/same-tree/description/


class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == NULL || q == NULL) {
            return p == q;
        }

        bool isLeftSame = isSameTree(p -> left, q -> left);      // Traverses through left side of tree in p and q
        bool isRightSame = isSameTree(p -> right, q -> right);   // Traverses through right side of tree in p and q
        
        return isLeftSame && isRightSame && p -> val == q -> val; // Returns if both the tree are same
    }
};