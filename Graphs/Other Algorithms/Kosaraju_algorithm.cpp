/*
🔄 Problem: Strongly Connected Components (Kosaraju’s Algorithm)

Given a directed graph,
find the number of Strongly Connected Components (SCCs).

-----------------------------------------------------

💡 What is an SCC?

A group of nodes where:
every node can reach every other node.

Example:
0 → 1 → 2 → 0
All belong to one SCC.

-----------------------------------------------------

💡 Approach: Kosaraju Algorithm

👉 Core Idea:
Use DFS twice + reverse graph

-----------------------------------------------------

🧠 Step 1: DFS + Stack (Finish Time Order)

- Run DFS on original graph
- After visiting all neighbours,
  push node into stack

👉 This gives nodes in decreasing
   order of finishing time

-----------------------------------------------------

🧠 Step 2: Reverse the Graph

For every edge:
u → v becomes v → u

-----------------------------------------------------

🧠 Step 3: DFS on Reversed Graph

- Pop nodes from stack
- If not visited:
    run DFS
    → this forms ONE SCC

- Count how many DFS runs happen

-----------------------------------------------------

💡 Why This Works:

Nodes with highest finish time
belong to "source SCCs" in reversed graph.

So we always pick correct SCC first.

-----------------------------------------------------

⏱ Time Complexity:
O(V + E)

- DFS 1: O(V + E)
- Reverse graph: O(V + E)
- DFS 2: O(V + E)

-----------------------------------------------------

📦 Space Complexity:
O(V + E)

- adjacency list
- reversed graph
- visited array
- stack
*/

#include <vector>
#include <stack>
using namespace std;    

class Solution {
private: 
    void dfs(int node, vector<int>& vis, vector<int> adj[], stack<int>& st) {
        vis[node] = 1;
        
        for(auto it : adj[node]) {
            
            if(!vis[it]) dfs(it, vis, adj, st);
        }
        
        st.push(node);
    }
    
private: 
    void dfs3(int node, vector<int>& vis, vector<int> adjT[]) {
        vis[node] = 1;
        
        for(auto it : adjT[node]) {
            
            if(!vis[it]) dfs3(it, vis, adjT);
        }
    }
    
public:
    int kosaraju(int V, vector<vector<int>> &edges) {
        
        vector<int> adj[V];
            for(auto it : edges) {
                int u = it[0];
                int v = it[1];
                adj[u].push_back(v);
            }
        
        vector<int> vis(V, 0);
        stack<int> st;
        
        for(int i = 0; i < V; i++) {
            if(!vis[i]) dfs(i, vis, adj, st);
        }
        
        vector<int> adjT[V];
        for(int i = 0; i < V; i++) {
            vis[i] = 0;
            for(auto it : adj[i]) {
                adjT[it].push_back(i);
            }
        }
            
        int scc = 0;
        
        while(!st.empty()) {
            int node = st.top(); st.pop();
            if(!vis[node]) {
                scc++;
                dfs3(node, vis, adjT);
            }
        }
        return scc;
    }
};