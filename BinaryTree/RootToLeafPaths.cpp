#include <bits/stdc++.h>
using namespace std;

/* ==========================================
   DFS Approach: Root-to-Leaf Paths
========================================== */
class DFSSolution {
public:
    vector<vector<int>> binaryTreePaths(TreeNode* root) {
        vector<vector<int>> allPaths;
        vector<int> path;
        dfs(root, path, allPaths);
        return allPaths;
    }

private:
    void dfs(TreeNode* node, vector<int>& path, vector<vector<int>>& allPaths) {
        if (!node) return;

        path.push_back(node->val); // add current node

        // if leaf, store the path
        if (!node->left && !node->right) {
            allPaths.push_back(path);
        } else {
            dfs(node->left, path, allPaths);
            dfs(node->right, path, allPaths);
        }

        path.pop_back(); // backtrack
    }
};

/* ==========================================
   BFS Approach: Root-to-Leaf Paths
========================================== */
class BFSSolution {
public:
    vector<vector<int>> binaryTreePaths(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return ans;

        queue<pair<TreeNode*, vector<int>>> q;
        q.push({root, {root->val}});

        while (!q.empty()) {
            auto [node, path] = q.front();
            q.pop();

            if (!node->left && !node->right) {
                ans.push_back(path); // leaf node
            } else {
                if (node->left) {
                    auto newPath = path;
                    newPath.push_back(node->left->val);
                    q.push({node->left, newPath});
                }
                if (node->right) {
                    auto newPath = path;
                    newPath.push_back(node->right->val);
                    q.push({node->right, newPath});
                }
            }
        }
        return ans;
    }
};