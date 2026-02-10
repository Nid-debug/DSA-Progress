class Solution {
public:
    int ans = 0;

    int height(TreeNode* root) {
        if (root == NULL) {                  // Returns 0 if tree is empty
            return 0;
        }

        int LeftHt = height(root->left);     // Calculates left side of the tree
        int RightHt = height(root->right);   // Calculates right side of the tree

        ans = max(LeftHt + RightHt, ans);    // Returns the longest path to solve the problem
        return max(LeftHt, RightHt) + 1;
    }


    int diameterOfBinaryTree(TreeNode* root) {
        height(root);

        return ans;
    }
};