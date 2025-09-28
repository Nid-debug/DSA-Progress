class Solution {
public:
    int search(vector<int>& inorder, int left, int right, int val) {
        for (int i = left; i <= right; i++) {
            if (inorder[i] == val) {
                return i;
            }
        }
        return -1;
    }

    TreeNode* helper(vector<int>& inorder, vector<int>& postorder, int& postIdx, int left, int right) {
        if (left > right) return NULL;

        // Take current root from postorder
        TreeNode* root = new TreeNode(postorder[postIdx]);

        int inIdx = search(inorder, left, right, postorder[postIdx]);
        postIdx--; // move to previous element

        // Build right subtree first, then left
        root->right = helper(inorder, postorder, postIdx, inIdx + 1, right);
        root->left  = helper(inorder, postorder, postIdx, left, inIdx - 1);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int postIdx = postorder.size() - 1; // start from last element
        return helper(inorder, postorder, postIdx, 0, inorder.size() - 1);
    }
};
