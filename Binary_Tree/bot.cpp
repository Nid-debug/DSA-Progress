#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ----------------- APPROACH 1 -----------------
    // Using map<int, int>
    // TC: O(N log N) because map insertions take logN
    // SC: O(N) for map + queue
    vector<int> bottomViewWithMap(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        map<int, int> mp; // (hd -> value), sorted automatically
        queue<pair<TreeNode*, int>> q; // (node, horizontal distance)
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();

            // store (overwrite) the value for each hd
            mp[hd] = node->val;

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        // Extract values in sorted order of hd
        for (auto& it : mp) {
            result.push_back(it.second);
        }
        return result;
    }

    // ----------------- APPROACH 2 -----------------
    // Using unordered_map<int, int> + min/max hd
    // TC: O(N) (average case, unordered_map insertions O(1))
    // SC: O(N) for unordered_map + queue
    vector<int> bottomViewWithUnorderedMap(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        unordered_map<int, int> mp; // (hd -> value)
        queue<pair<TreeNode*, int>> q; // (node, hd)

        int minHd = 0, maxHd = 0;
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();

            // overwrite the value for each hd (last one stays)
            mp[hd] = node->val;

            minHd = min(minHd, hd);
            maxHd = max(maxHd, hd);

            if (node->left) q.push({node->left, hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        // Collect results in sorted order using minHd..maxHd
        for (int hd = minHd; hd <= maxHd; hd++) {
            // if (mp.count(hd)) {
            //     result.push_back(mp[hd]);
            // }
            result.push_back(mp[hd]);
        }
        return result;
    }
};