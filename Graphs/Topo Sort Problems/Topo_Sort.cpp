#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class SolutionBFS {
public:
    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0);

        for(int i = 0; i < V; i++)
            for(auto it : adj[i])
                indegree[it]++;

        queue<int> q;
        for(int i = 0; i < V; i++)
            if(indegree[i] == 0) q.push(i);

        vector<int> topo;
        while(!q.empty()) {
            int node = q.front(); q.pop();
            topo.push_back(node);
            for(auto it : adj[node]) {
                indegree[it]--;
                if(indegree[it] == 0) q.push(it);
            }
        }
        return topo; // if topo.size() != V, cycle exists
    }
};

class SolutionDFS {
public:
    void dfs(int node, vector<bool>& vis, vector<int> adj[], stack<int>& st) {
        vis[node] = true;
        for(auto it : adj[node])
            if(!vis[it]) dfs(it, vis, adj, st);
        st.push(node); // push AFTER all neighbours are done
    }

    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<bool> vis(V, false);
        stack<int> st;

        for(int i = 0; i < V; i++)
            if(!vis[i]) dfs(i, vis, adj, st);

        vector<int> topo;
        while(!st.empty()) {
            topo.push_back(st.top());
            st.pop();
        }
        return topo;
    }
};