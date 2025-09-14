// LeetCode Problem 144: Binary Tree Preorder Traversal
// Link: https://leetcode.com/problems/binary-tree-preorder-traversal/

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorder(root, result);
        return result;
    }

private:
    void preorder(TreeNode* node, vector<int>& result) {
        if (!node) return;
        result.push_back(node->val);   // Visit root
        preorder(node->left, result);  // Visit left
        preorder(node->right, result); // Visit right
    }
};
