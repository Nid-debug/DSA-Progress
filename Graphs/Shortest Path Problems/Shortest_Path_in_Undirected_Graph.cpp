/*
🧩 Problem: Shortest Path in Undirected Graph (Unit Weights)

Given an undirected graph with V vertices and edges,
find the shortest distance from a given source node (src)
to all other nodes.

All edges have equal weight = 1.
-----------------------------------------------------

⏱ Time Complexity:
- Building graph: O(E)
- BFS traversal: O(V + E)
=> Overall: O(V + E)

📦 Space Complexity:
- Adjacency list: O(V + E)
- Distance array + queue: O(V)
=> Overall: O(V + E)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
  public:
    vector<int> shortestPath(int V, vector<vector<int>> &edges, int src) {
        vector<int> adj[V];
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u); // undirected!
        }

        vector<int> dist(V, -1);
        dist[src] = 0;

        queue<int> q;
        q.push(src);

        while(!q.empty()) {
            int node = q.front(); q.pop();

            for(auto it : adj[node]) {
                if(dist[it] == -1) { // not visited
                    dist[it] = dist[node] + 1;
                    q.push(it);
                }
            }
        }
        return dist;
    }
};