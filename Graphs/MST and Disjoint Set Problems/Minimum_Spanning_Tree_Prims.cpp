#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
  public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        
        vector<pair<int, int>> adj[V];
        
        for(auto it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        priority_queue<pair<int, int>, vector<pair<int ,int>>,
        greater<pair<int, int>>> pq;
        
        vector<int> vis(V, 0);
        pq.push({0, 0});
        int sum = 0;
        
        while(!pq.empty()) {
            auto[wt, node] = pq.top();
            pq.pop();
            
            if(vis[node]) continue;
    
            vis[node] = 1;
            sum += wt;
            
            for(auto[adjNode, edgeW] : adj[node]) {
                if(!vis[adjNode]) {
                    pq.push({edgeW, adjNode});
                }
            }
        }
        return sum;
    }
};