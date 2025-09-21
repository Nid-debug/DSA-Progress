/*
    Problem: Top View of a Binary Tree
    ----------------------------------
    Given a binary tree, return the top view of the tree.
    The "top view" means the set of nodes visible when the tree is viewed from the top.

    Approach 1: Using map<int,int> (Ordered Map)
    Approach 2: Using unordered_map<int,int> with min/max horizontal distance
*/

class Solution
{
public:
    // ----------------- APPROACH 1 -----------------
    // Using map<int, int>
    // TC: O(N log N) because map insertions take logN
    // SC: O(N) for map + queue
    vector<int> topViewWithMap(TreeNode *root)
    {
        vector<int> result;
        if (root == NULL) return result;

        map<int, int> mp;               // (hd -> value), sorted automatically
        queue<pair<TreeNode *, int>> q; // (node, horizontal distance)
        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            // store only first occurrence of each hd
            if (mp.find(hd) == mp.end())
            {
                mp[hd] = node->val;
            }

            if (node->left)
                q.push({node->left, hd - 1});
            if (node->right)
                q.push({node->right, hd + 1});
        }

        // Extract values in sorted order of hd
        for (auto &it : mp)
        {
            result.push_back(it.second);
        }
        return result;
    }

    // ----------------- APPROACH 2 -----------------
    // Using unordered_map<int, int> + min/max hd
    // TC: O(N) (average case, unordered_map insertions O(1))
    // SC: O(N) for unordered_map + queue
    vector<int> topViewWithUnorderedMap(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr) return result;

        unordered_map<int, int> mp;     // (hd -> value)
        queue<pair<TreeNode *, int>> q; // (node, hd)

        int minHd = 0, maxHd = 0;
        q.push({root, 0});

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            // store only first occurrence of hd
            if (mp.find(hd) == mp.end())
            {
                mp[hd] = node->val;
            }

            minHd = min(minHd, hd);
            maxHd = max(maxHd, hd);

            if (node->left)
                q.push({node->left, hd - 1});
            if (node->right)
                q.push({node->right, hd + 1});
        }

        // Collect results in sorted order using minHd..maxHd
        for (int hd = minHd; hd <= maxHd; hd++)
        {
            if (mp.count(hd))
            {
                result.push_back(mp[hd]);
            }
        }
        return result;
    }
};