/*
🏝️ Problem: Number of Islands II

You are given:
- An empty m x n grid filled with water
- A list of positions where land is added one by one

Goal:
After each land addition,
return the number of islands.

-----------------------------------------------------

💡 Approach:

👉 Use Disjoint Set Union (DSU / Union Find)

Why?
- Every new land cell initially forms a new island
- If adjacent lands already exist:
    merge them into one island

-----------------------------------------------------

🧠 Key Idea:

1. Convert 2D cell into 1D node:
   node = row * n + col

2. Initially:
   parent[node] = -1
   meaning water

3. When land is added:
   - Make parent[node] = node
   - count++

4. Check 4 neighbours:
   - If neighbour is land: union both cells

5. Every successful union:
   - reduces island count by 1

-----------------------------------------------------

🧠 Duplicate Position Handling:

If land already exists:
- island count remains same
- simply push current count

-----------------------------------------------------

⚠️ Key Insight:

Adding new land:
- creates a new island

Unioning neighbouring lands:
- merges islands together

-----------------------------------------------------

⏱ Time Complexity:

For K operations: Each DSU operation: almost O(1)

Final TC:
- O(K × α(N))

Where: α(N) = inverse Ackermann function (practically constant)

-----------------------------------------------------

📦 Space Complexity:

- parent array
- rank array

Final SC: O(m × n)
*/

#include <vector>
using namespace std;

class Solution {
public:
    int find(int node, vector<int>& parent) {
        if(parent[node] != node)
            parent[node] = find(parent[node], parent);
        return parent[node];
    }

    void unionNodes(int u, int v, vector<int>& parent, vector<int>& rank, int& count) {
        int pu = find(u, parent);
        int pv = find(v, parent);
        if(pu == pv) return; // already same component

        if(rank[pu] < rank[pv]) parent[pu] = pv;
        else if(rank[pu] > rank[pv]) parent[pv] = pu;
        else { parent[pv] = pu; rank[pu]++; }

        count--; // two islands merged into one
    }

    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> parent(m * n, -1); // -1 means water
        vector<int> rank(m * n, 0);
        vector<pair<int,int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

        int count = 0;
        vector<int> result;

        for(auto& pos : positions) {
            int row = pos[0], col = pos[1];
            int node = row * n + col; // convert 2D to 1D

            // if already land skip (duplicate position)
            if(parent[node] != -1) {
                result.push_back(count);
                continue;
            }

            // new land cell → new island
            parent[node] = node;
            count++;

            // check all 4 neighbours
            for(auto [dr, dc] : dirs) {
                int nr = row + dr;
                int nc = col + dc;
                int neighbour = nr * n + nc;

                // if neighbour is valid and is land
                if(nr >= 0 && nr < m && nc >= 0 && nc < n && parent[neighbour] != -1)
                    unionNodes(node, neighbour, parent, rank, count);
            }
            result.push_back(count);
        }
        return result;
    }
};