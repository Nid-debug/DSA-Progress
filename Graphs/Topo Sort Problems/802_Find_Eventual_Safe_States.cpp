/*
===========================================================
🧩 Problem: Eventual Safe States
===========================================================

Given a directed graph where adj[i] represents nodes that node i points to,
find all nodes that are eventually safe.

A node is SAFE if:
- Every path starting from that node leads to a terminal node
- A terminal node is one with no outgoing edges

-----------------------------------------------------------
💡 Intuition:
-----------------------------------------------------------
- Unsafe nodes are part of cycles OR lead to cycles
- Safe nodes eventually lead to terminal nodes

👉 Reverse Thinking (Key Trick):
Instead of detecting cycles directly:
1. Reverse the graph
2. Apply Kahn's Algorithm (Topological Sort using BFS)

Steps:
- Reverse edges: u → v becomes v → u
- Compute indegree in reversed graph
- Nodes with indegree 0 = terminal nodes (safe)
- Do BFS and remove nodes layer by layer
- Remaining nodes (not visited) are part of cycles

-----------------------------------------------------------
⏱ Complexity:
-----------------------------------------------------------
Time  : O(V + E + V log V) // the sort at the end adds V log V
Space : O(V + E)
===========================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& adj) {
        int v = adj.size();
        vector<int> adjRev[v];
        vector<int> indegree(v, 0);

        for (int i = 0; i < v; i++) {
            for(auto it : adj[i]) {
                adjRev[it].push_back(i);
                indegree[i]++;
            }
        }

        queue<int> q;
        for(int i = 0; i < v; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> ans;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            ans.push_back(node);
            for(auto it : adjRev[node]) {
                indegree[it]--;
                if(indegree[it] == 0) q.push(it);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};