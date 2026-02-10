// LeetCode 235. Lowest Common Ancestor of a Binary Search Tree

class Solution {
public:
    // Recursive Approach
    TreeNode* lowestCommonAncestorRecursive(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        // If both nodes are smaller, go left
        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestorRecursive(root->left, p, q);

        // If both nodes are greater, go right
        if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestorRecursive(root->right, p, q);

        // Split point — current node is LCA
        return root;
    }

    // Iterative Approach
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } 
            else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } 
            else {
                return root; // Split point -> LCA found
            }
        }
        return nullptr;
    }
};