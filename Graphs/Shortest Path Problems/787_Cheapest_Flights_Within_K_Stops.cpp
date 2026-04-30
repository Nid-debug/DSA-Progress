/*
===========================================================
✈️ Problem: Cheapest Flights Within K Stops
===========================================================

You are given:
- n cities (0 to n-1)
- flights[i] = {u, v, price}
- src → starting city
- dst → destination city
- k → maximum stops allowed

Return the cheapest price from src to dst with at most k stops.
If not possible, return -1.

-----------------------------------------------------------
💡 Intuition:
-----------------------------------------------------------
- This looks like shortest path, BUT with constraint on stops

👉 Why NOT pure Dijkstra?
- Because we must limit number of stops
- A cheaper path with more stops might be invalid

👉 Approach:
Use BFS (level-wise traversal based on stops)

Steps:
1. Build adjacency list
2. Use queue: {node, currentCost}
3. Each level in BFS = 1 stop
4. Relax edges only if cost improves
5. Stop when stops > k

-----------------------------------------------------------
🔁 Key Idea:
-----------------------------------------------------------
- We process nodes level-by-level (like BFS)
- Each level = number of stops used
- This ensures we respect k constraint

-----------------------------------------------------------
⏱ Complexity:
-----------------------------------------------------------
Time  : O(K × E)
Space : O(N + E)
===========================================================
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

        // Adjacency list: {node → {adjNode, price}}
        vector<vector<pair<int, int>>> adj(n);

        for (auto& flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        // Distance array (minimum cost to reach each node)
        vector<int> dist(n, 1e9);
        dist[src] = 0;

        // Queue: {node, current cost}
        queue<pair<int, int>> q;
        q.push({src, 0});

        int stops = 0;

        // BFS with stop constraint
        while (!q.empty() && stops <= k) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                auto [node, cost] = q.front();
                q.pop();

                for (auto& [adjNode, price] : adj[node]) {

                    // Relaxation step
                    if (cost + price < dist[adjNode]) {
                        dist[adjNode] = cost + price;
                        q.push({adjNode, dist[adjNode]});
                    }
                }
            }
            stops++;
        }
        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};