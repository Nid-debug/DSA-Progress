/*
🌐 Problem: Number of Provinces (Using Disjoint Set / Union-Find)

-----------------------------------------------------

💡 Approach (Disjoint Set / Union-Find):

1. Treat each city as a separate component initially.
2. Use DSU (Disjoint Set) with:
   - Path Compression (optimize find)
   - Union by Rank (keep tree shallow)

3. For every pair (i, j):
   - If connected → union(i, j)

4. Count how many nodes are their own parent:
   → number of provinces

-----------------------------------------------------

⚠️ Key Idea:
- Instead of DFS/BFS → use DSU to group components efficiently
- DSU is especially useful when:
  → dynamic connectivity
  → merging sets

-----------------------------------------------------

⏱ Time Complexity:
- Union-Find operations ≈ O(α(n)) (almost constant)
- Traversing matrix: O(n²)
=> Overall: O(n²)

📦 Space Complexity:
- Parent + Rank arrays: O(n)
*/

#include <vector>
using namespace std;

class Solution {
public:
    // find with path compression
    int find(int node, vector<int>& parent) {
        if(parent[node] != node)
            parent[node] = find(parent[node], parent); // path compression
        return parent[node];
    }

    // union by rank
    void unionNodes(int u, int v, vector<int>& parent, vector<int>& rank) {
        int pu = find(u, parent);
        int pv = find(v, parent);

        if(pu == pv) return; // already in same component

        // attach smaller rank tree under larger rank tree
        if(rank[pu] < rank[pv])
            parent[pu] = pv;
        else if(rank[pu] > rank[pv])
            parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();

        // initially every node is its own parent
        vector<int> parent(n), rank(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;

        // union connected cities
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(isConnected[i][j] == 1)
                    unionNodes(i, j, parent, rank);
            }
        }

        // count number of distinct components (nodes that are their own parent)
        int provinces = 0;
        for(int i = 0; i < n; i++)
            if(find(i, parent) == i) provinces++;

        return provinces;
    }
};