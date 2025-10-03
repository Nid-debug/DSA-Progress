class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);

        if(root->val < val) {
            root->right = insertIntoBST(root->right, val);  // Right Subtree
        }
        else{
            root->left = insertIntoBST(root->left, val);    // Left Subtree
        }
        return root;
    }
};