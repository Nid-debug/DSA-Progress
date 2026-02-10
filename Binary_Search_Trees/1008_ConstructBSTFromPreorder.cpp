// LeetCode 1008. Construct Binary Search Tree from Preorder Traversal
// Includes both Brute Force and Optimized Recursive Approaches

// ------------------------------------------------------------
// Brute Force Recursive Approach (O(N²) Time, O(N²) Space)
// ------------------------------------------------------------
class SolutionBruteForce {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if (preorder.empty()) return nullptr;

        int rootVal = preorder[0];
        TreeNode* root = new TreeNode(rootVal);

        vector<int> left, right;
        for (int i = 1; i < preorder.size(); i++) {
            if (preorder[i] < rootVal)
                left.push_back(preorder[i]);
            else
                right.push_back(preorder[i]);
        }

        root->left = bstFromPreorder(left);
        root->right = bstFromPreorder(right);

        return root;
    }
};

// ------------------------------------------------------------
// Optimized Recursive Approach (O(N) Time, O(H) Space)
// ------------------------------------------------------------
class Solution {
public:
    TreeNode* buildBST(vector<int>& preorder, int& i, int bound) {
        if (i >= preorder.size() || preorder[i] > bound)
            return nullptr;

        TreeNode* root = new TreeNode(preorder[i++]);
        root->left = buildBST(preorder, i, root->val);
        root->right = buildBST(preorder, i, bound);
        
        return root;
    }

    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return buildBST(preorder, i, INT_MAX);
    }
};

/*
Example:
Input:  preorder = [8, 5, 1, 7, 10, 12]
Output: [8, 5, 10, 1, 7, null, 12]

BST Structure:
        8
       / \
      5   10
     / \    \
    1   7    12
*/
