/*
🧩 Problem: Shortest Path in DAG

Given a Directed Acyclic Graph (DAG) with V vertices and E edges,
find the shortest path from source node 0 to all other nodes.

Each edge has a weight.
-----------------------------------------------------

⏱ Time Complexity:
- Topo sort (DFS): O(V + E)
- Relaxation: O(E)
=> Overall: O(V + E)

📦 Space Complexity:
- Adjacency list: O(V + E)
- Visited + stack + dist: O(V)
=> Overall: O(V + E)
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
private:
    void topoSort(int node, vector<pair<int,int>> adj[], vector<bool>& vis, stack<int>& st) {
        vis[node] = true;
        for(auto it : adj[node])
            if(!vis[it.first]) topoSort(it.first, adj, vis, st);
        st.push(node);
    }

public:
    vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) {
        vector<pair<int,int>> adj[V];
        for(int i = 0; i < E; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            adj[u].push_back({v, wt});
        }

        vector<bool> vis(V, false);
        stack<int> st;
        for(int i = 0; i < V; i++)
            if(!vis[i]) topoSort(i, adj, vis, st);

        vector<int> dist(V, 1e9);
        dist[0] = 0;

        while(!st.empty()) {
            int node = st.top();
            st.pop();

            for(auto it : adj[node]) {
                int v = it.first;
                int wt = it.second;
                if(dist[node] + wt < dist[v])
                    dist[v] = dist[node] + wt;
            }
        }

        // convert unreachable nodes to -1
        for(int i = 0; i < V; i++)
            if(dist[i] == 1e9) dist[i] = -1;

        return dist;
    }
};