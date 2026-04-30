/*
===========================================================
📡 Problem: Network Delay Time
===========================================================

You are given:
- n nodes (1 to n)
- times[i] = {u, v, w} → time to travel from u → v
- k → starting node

Return the time it takes for all nodes to receive the signal.
If not all nodes can be reached, return -1.

👉 Answer = maximum time among all shortest paths from k

-----------------------------------------------------------
💡 Intuition:
-----------------------------------------------------------
- Classic shortest path problem
- Need shortest time from source (k) to all nodes

👉 Use Dijkstra’s Algorithm:
1. Use min-heap (priority queue)
2. Store {time, node}
3. Relax edges when shorter path found
4. Compute shortest distance to all nodes

Final Answer:
- Take maximum distance among all nodes
- If any node is unreachable → return -1

-----------------------------------------------------------
🔁 Why Dijkstra?
-----------------------------------------------------------
- Graph is weighted (positive weights)
- Need shortest path from one source to all nodes

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
#include <algorithm>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n + 1); // 1-indexed
        for(auto& time : times){
            adj[time[0]].push_back({time[1], time[2]});
        }

        vector<int> dist(n + 1, 1e9);
        dist[k] = 0;

        // min heap: {cost, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, k});

        while(!pq.empty()) {
            auto [cost, node] = pq.top(); pq.pop();

            if(cost > dist[node]) continue;

            for(auto [neighbour, weight] : adj[node]) {
                if(dist[node] + weight < dist[neighbour]) {
                    dist[neighbour] = dist[node] + weight;
                    pq.push({dist[neighbour], neighbour});
                }
            }
        }
        int maxDist = *max_element(dist.begin() + 1, dist.end());
        return maxDist == 1e9 ? -1 : maxDist;     
    }
};