/*
🔌 Problem: Number of Operations to Make Network Connected

Given:
- n computers (0 to n-1)
- connections where each connection[i] = {u, v}

Goal:
Find the minimum number of operations to connect all computers.

Rules:
- You can remove an existing cable and place it anywhere
- If not possible → return -1

-----------------------------------------------------

💡 Approach (Disjoint Set / Union-Find):

1. Use DSU to group connected components.
2. For each connection:
   - If u and v are already connected → it's a "spare cable"
   - Else → union them

3. Count number of connected components.

4. To connect k components → need (k - 1) edges.

5. If spare cables ≥ (components - 1) → possible
   else → return -1

-----------------------------------------------------

⚠️ Key Idea:
- Extra edges = reusable resources
- Required edges = (components - 1)

-----------------------------------------------------

⏱ Time Complexity:
- DSU operations: ~O(α(n)) (almost constant)
- Loop over connections: O(E)
- Counting components: O(n)
=> Overall: O(n + E)

📦 Space Complexity:
- Parent + Rank arrays: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

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

        if(rank[pu] < rank[pv])
            parent[pu] = pv;
        else if(rank[pu] > rank[pv])
            parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        vector<int> parent(n), rank(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;

        int spare = 0; // redundant cables

        for(auto& conn : connections) {
            int u = conn[0], v = conn[1];

            if(find(u, parent) == find(v, parent))
                spare++; // already in same component → spare cable
            else
                unionNodes(u, v, parent, rank); // merge components
        }

        // count number of components
        int components = 0;
        for(int i = 0; i < n; i++)
            if(find(i, parent) == i) components++;

        // need components-1 cables to connect all components
        if(spare >= components - 1) return components - 1;
        return -1;
    }
};