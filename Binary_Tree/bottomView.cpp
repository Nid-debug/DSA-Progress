// bottom_view.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // ----------------- APPROACH 1 -----------------
    // Using map<int,int> (ordered)
    // Time: O(N log N) due to map insertions (log K) where K = distinct HDs (<= N)
    // Space: O(N) for map + queue
    vector<int> bottomViewWithMap(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;

        map<int, int> mp; // hd -> value (ordered by hd)
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 0));

        while (!q.empty()) {
            pair<TreeNode*, int> p = q.front();
            q.pop();
            TreeNode* node = p.first;
            int hd = p.second;

            // overwrite so the last node at this hd (level order) remains
            mp[hd] = node->val;

            if (node->left)  q.push(make_pair(node->left,  hd - 1));
            if (node->right) q.push(make_pair(node->right, hd + 1));
        }

        for (auto &it : mp) result.push_back(it.second);
        return result;
    }

    // ----------------- APPROACH 2 -----------------
    // Using unordered_map<int,int> + min/max hd
    // Time: O(N) average (unordered_map O(1) avg)
    // Space: O(N) for unordered_map + queue
    vector<int> bottomViewWithUnorderedMap(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;

        unordered_map<int, int> mp; // hd -> value (unsorted)
        queue<pair<TreeNode*, int>> q;
        int minHd = 0, maxHd = 0;

        q.push(make_pair(root, 0));
        while (!q.empty()) {
            pair<TreeNode*, int> p = q.front();
            q.pop();
            TreeNode* node = p.first;
            int hd = p.second;

            // overwrite: last seen (lowest level / BFS order) remains
            mp[hd] = node->val;

            minHd = min(minHd, hd);
            maxHd = max(maxHd, hd);

            if (node->left)  q.push(make_pair(node->left,  hd - 1));
            if (node->right) q.push(make_pair(node->right, hd + 1));
        }

        // collect in sorted order using min..max
        for (int hd = minHd; hd <= maxHd; ++hd) {
            auto it = mp.find(hd);
            if (it != mp.end()) result.push_back(it->second);
        }
        return result;
    }
};

// ----------------- DRIVER -----------------
int main() {
    /*
         Example tree:
                 20
               /    \
              8      22
             / \       \
            5   3       25
               / \
             10  14

        Expected Bottom View: [5, 10, 3, 14, 25]
    */

    TreeNode* root = new TreeNode(20);
    root->left = new TreeNode(8);
    root->right = new TreeNode(22);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(25);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(14);

    Solution sol;

    vector<int> outMap = sol.bottomViewWithMap(root);
    cout << "Bottom View (map): ";
    for (int v : outMap) cout << v << " ";
    cout << "\n";

    vector<int> outUnord = sol.bottomViewWithUnorderedMap(root);
    cout << "Bottom View (unordered_map): ";
    for (int v : outUnord) cout << v << " ";
    cout << "\n";

    return 0;
}
