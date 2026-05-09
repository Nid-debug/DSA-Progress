/*
🌉 Problem: Critical Connections in a Network (Bridges in Graph)

Given an undirected graph with n nodes and connections,
find all critical connections (bridges).

A bridge is an edge which, if removed,
increases the number of connected components.

-----------------------------------------------------

💡 Key Idea:

An edge (u → v) is a bridge if:
there is NO alternative path from v back to u.

Formally:
low[v] > tin[u]

-----------------------------------------------------

🧠 Concepts Used:

1. tin[node]:
   → Time of insertion (when node is first visited)

2. low[node]:
   → Lowest time reachable from that node
     (including back edges)

-----------------------------------------------------

🧠 DFS Logic:

For every node:
- Mark visited
- Assign tin and low

For each neighbour:
-----------------------------------------------------

CASE 1: neighbour == parent
→ Ignore (undirected graph)

CASE 2: not visited
→ DFS call
→ update low[node] = min(low[node], low[neighbour])

→ Check for bridge:
   if(low[neighbour] > tin[node])
       edge is a bridge

CASE 3: already visited (back edge)
→ update low[node] = min(low[node], tin[neighbour])

-----------------------------------------------------

💡 Why Bridge Condition Works:

If low[child] > tin[parent],
it means:
child cannot reach parent or above
without using that edge.

So removing it disconnects graph.

-----------------------------------------------------

⏱ Time Complexity:
O(V + E)

- DFS traversal of graph

-----------------------------------------------------

📦 Space Complexity:
O(V + E)

- adjacency list
- tin & low arrays
- recursion stack
*/

#include <vector>
using namespace std;

class Solution {
private:
    int timer = 1;

public:
    void dfs(int node, int parent, vector<int>& vis, vector<int> adj[],
        vector<int>& tin, vector<int>& low, vector<vector<int>>& bridges) {

        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        for(auto it : adj[node]) {
            if(it == parent) continue;
            if(!vis[it]) {
                dfs(it, node, vis, adj, tin, low, bridges);
                low[node] = min(low[node], low[it]);

                if(low[it] > tin[node]) {
                    bridges.push_back({it, node});
                }
            }
            else low[node] = min(low[node], tin[it]);
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> adj[n];
        for(auto it : connections) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        vector<int> vis(n ,0);
        vector<int> tin(n);
        vector<int> low(n);
        vector<vector<int>> bridges;
        
        dfs(0, -1, vis, adj, tin, low, bridges);
        return bridges;
    }
};