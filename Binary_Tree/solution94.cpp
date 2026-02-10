// LeetCode Problem 94: Binary Tree Inorder Traversal
// Link: https://leetcode.com/problems/binary-tree-inorder-traversal/

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        inorder(root, ans);
        return ans;
    }

    private:
    void inorder(TreeNode* node, vector<int>& ans) {
        if (node == NULL) return;
   
        inorder(node->left, ans);
        ans.push_back(node->val);  
        inorder(node->right, ans); 
    }
};