class Solution {
public:
    // ---------- Inorder Predecessor ----------
    TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
        TreeNode* predecessor = nullptr;

        while (root) {
            if (p->val <= root->val) {
                root = root->left; // predecessor must be smaller
            } else {
                predecessor = root; // possible predecessor
                root = root->right;
            }
        }
        return predecessor; 
    }

    // ---------- Inorder Successor ----------
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* successor = nullptr;

        while (root) {
            if (p->val >= root->val) {
                root = root->right; // successor must be greater
            } else {
                successor = root; // possible successor
                root = root->left;
            }
        }
        return successor; // nullptr if none
    }
};