/*
===========================================================
🛣️ Problem: Number of Ways to Arrive at Destination
===========================================================

Find:
👉 Number of distinct ways to reach node (n-1) from node 0
👉 Such that the total travel time is MINIMUM

Return answer modulo 1e9 + 7

-----------------------------------------------------------
💡 Intuition:
-----------------------------------------------------------
- This is NOT just shortest path
- We also need to count number of shortest paths

👉 Use Dijkstra + Path Counting

Steps:
1. Maintain:
   - dist[i] = shortest distance to node i
   - ways[i] = number of shortest ways to reach i

2. While relaxing edges:
   - If shorter path found:
        update dist
        copy ways
   - If equal path found:
        add ways

-----------------------------------------------------------
⏱ Complexity:
-----------------------------------------------------------
Time  : O(E log V)
Space : O(V + E)
===========================================================
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int mod = (int)(1e9 + 7);

        vector<vector<pair<long,long>>> adj(n);
        for(auto& it : roads) {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }

        vector<long> dist(n, __LONG_MAX__), ways(n, 0);
        dist[0] = 0;
        ways[0] = 1;

        priority_queue<pair<long,long>, vector<pair<long,long>>, greater<>> pq;
        pq.push({0, 0});

        while(!pq.empty()) {
            auto[weight, node] = pq.top(); pq.pop();

            if(weight > dist[node]) continue;

            for(auto [neighbour, edgeW] : adj[node]) {
                if(weight + edgeW < dist[neighbour]) {
                    dist[neighbour] = weight + edgeW;
                    pq.push({dist[neighbour], neighbour});
                    ways[neighbour] = ways[node];
                }
                else if(weight + edgeW == dist[neighbour]) {
                    ways[neighbour] = (ways[neighbour] + ways[node]) % mod;
                }
            }
        }
        return ways[n-1] % mod;
    }
};