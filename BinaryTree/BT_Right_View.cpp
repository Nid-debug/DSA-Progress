#include <bits/stdc++.h>
using namespace std;

// -------------------- Solution Class --------------------
class Solution {
public:
    // ======================================================
    // Approach 1: BFS (Level Order Traversal)
    // ======================================================
    /*
        Logic:
        - Traverse the tree level by level using a queue.
        - At each level, the last node is visible from the right side.
        - Push that node into result vector.
        Time Complexity : O(N)  -> each node is visited once
        Space Complexity: O(N)  -> queue can hold up to N/2 nodes in worst case
    */
    vector<int> rightSideView_BFS(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

                // If this is the last node of current level, add to answer
                if (i == size - 1) {
                    ans.push_back(node->val);
                }

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return ans;
    }

    
    // ======================================================
    // Approach 2: DFS (Right-first Preorder Traversal)
    // ======================================================
    /*
        Logic:
        - Traverse preorder but go Right first (Root -> Right -> Left).
        - Maintain depth variable.
        - The first node visited at each depth is the rightmost node.
        Time Complexity : O(N)
        Space Complexity: O(H) -> recursion stack (H = tree height)
    */
    void dfs(TreeNode* node, int depth, vector<int>& ans) {
        if (!node) return;

        // If this level is reached for the first time
        if (depth == ans.size()) {
            ans.push_back(node->val);
        }

        // Go right first to ensure rightmost nodes are picked
        dfs(node->right, depth + 1, ans);
        dfs(node->left, depth + 1, ans);
    }

    vector<int> rightSideView_DFS(TreeNode* root) {
        vector<int> ans;
        dfs(root, 0, ans);
        return ans;
    }
};