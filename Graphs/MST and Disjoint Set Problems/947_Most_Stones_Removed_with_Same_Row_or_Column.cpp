/*
🪨 Problem: Most Stones Removed with Same Row or Column

Given stones placed on a 2D grid,
you may remove a stone if another stone exists
in the same row or same column.

Goal:
Return the maximum number of stones that can be removed.

-----------------------------------------------------

💡 Key Observation:

If stones are connected through rows/columns,
they form one connected component.

In one connected component:
- We can remove all stones except one

So:

answer = total stones - number of connected components

-----------------------------------------------------

🧠 Approach 1: DSU on Stone Indices

👉 Idea:
- Treat every stone as a node
- Connect two stones if: same row OR same column

Then:
- Count connected components
- answer = n - components

-----------------------------------------------------

⏱ Time Complexity:
- O(N² × α(N))
  (checking every pair of stones)

📦 Space Complexity:
- O(N)

-----------------------------------------------------

🧠 Approach 2: Optimized DSU (Rows + Columns)

👉 Key Idea:
- Treat rows and columns as nodes

Example:
stone = [2,3]

Connect:
row 2 ↔ col 3

To avoid collision:
column node becomes: col + maxRow + 1

-----------------------------------------------------

💡 Why This Works:

If two stones share:
- same row → same row node
- same column → same column node

They automatically become connected.

-----------------------------------------------------

⏱ Time Complexity:
- O(N × α(N))

📦 Space Complexity:
- O(maxRow + maxCol)

-----------------------------------------------------

⚠️ Important Insight:

Maximum removable stones = total stones - connected components
*/

#include <vector>
#include <unordered_set>    
using namespace std;

// =====================================================
// Approach 1: DSU on Stone Indices
// =====================================================

class Solution {
public:
    int find(int node, vector<int>& parent) {
        if(parent[node] != node)
            parent[node] = find(parent[node], parent);

        return parent[node];
    }

    void unionNodes(int u, int v, vector<int>& parent, vector<int>& rank) {

        int pu = find(u, parent);
        int pv = find(v, parent);

        if(pu == pv) return;

        if(rank[pu] < rank[pv]) {
            parent[pu] = pv;
        }
        else if(rank[pv] < rank[pu]) {
            parent[pv] = pu;
        }
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    int removeStones(vector<vector<int>>& stones) {

        int n = stones.size();

        vector<int> parent(n);
        vector<int> rank(n, 0);

        // initially every stone is its own parent
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }

        // connect stones having same row or same column
        for(int i = 0; i < n; i++) {

            for(int j = i + 1; j < n; j++) {

                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {

                    unionNodes(i, j, parent, rank);
                }
            }
        }

        // count connected components
        int components = 0;

        for(int i = 0; i < n; i++) {
            if(find(i, parent) == i) components++;
        }

        return n - components;
    }
};

// =====================================================
// Approach 2: Optimized DSU (Rows + Columns)
// =====================================================

class SolutionOptimal {
public:
    int find(int node, vector<int>& parent) {
        if(parent[node] != node)
            parent[node] = find(parent[node], parent);
        return parent[node];
    }

    void unionNodes(int u, int v, vector<int>& parent, vector<int>& rank) {
        int pu = find(u, parent);
        int pv = find(v, parent);
        if(pu == pv) return;

        if(rank[pu] < rank[pv]) parent[pu] = pv;
        else if(rank[pu] > rank[pv]) parent[pv] = pu;
        else { parent[pv] = pu; rank[pu]++; }
    }

    int removeStones(vector<vector<int>>& stones) {
        // find max row and max col
        int maxRow = 0, maxCol = 0;
        for(auto& stone : stones) {
            maxRow = max(maxRow, stone[0]);
            maxCol = max(maxCol, stone[1]);
        }

        // parent size = maxRow + maxCol + 2
        int maxNode = maxRow + maxCol + 2;
        vector<int> parent(maxNode), rank(maxNode, 0);
        for(int i = 0; i < maxNode; i++) parent[i] = i;

        // union row with col+maxRow+1 for each stone
        for(auto& stone : stones)
            unionNodes(stone[0], stone[1] + maxRow + 1, parent, rank);

        // count distinct components that have at least one stone
        unordered_set<int> components;
        for(auto& stone : stones)
            components.insert(find(stone[0], parent));

        return stones.size() - components.size();
    }
};