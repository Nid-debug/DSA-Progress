// LeetCode Problem 145: Binary Tree Postorder Traversal
// Link: https://leetcode.com/problems/binary-tree-postorder-traversal/

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        postorder(root, ans);
        return ans;
    }

    private:
    void postorder(TreeNode* node, vector<int>& ans) {
        if (node == NULL) return;
   
        postorder(node->left, ans);
        postorder(node->right, ans);
        ans.push_back(node->val);   
    }
};