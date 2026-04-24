/*
    🎨 Bipartite Graph (DFS + BFS)

    🔹 Problem:
    Given an undirected graph, determine if it is bipartite.
    A graph is bipartite if we can divide nodes into 2 sets such that:
    - No two adjacent nodes belong to the same set

    🔹 Idea:
    - Try coloring the graph using 2 colors (0 and 1)
    - Adjacent nodes must have opposite colors
    - If conflict occurs → NOT bipartite

    🔹 Handle:
    - Graph can be disconnected → check all components

    🔹 Time Complexity: O(V + E)
    🔹 Space Complexity: O(V)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class SolutionDFS {
public:
    bool dfs(int node, int color, vector<int>& colorArr, vector<vector<int>>& graph) {
        colorArr[node] = color;

        for(int neighbour : graph[node]) {
            if(colorArr[neighbour] == -1) { // not visited
                if(!dfs(neighbour, 1 - color, colorArr, graph)) return false;
            }
            else if(colorArr[neighbour] == color) // same color as current = not bipartite
                return false;
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> colorArr(n, -1); // -1 = unvisited

        for(int i = 0; i < n; i++) {
            if(colorArr[i] == -1) { // handle disconnected components
                if(!dfs(i, 0, colorArr, graph)) return false;
            }
        }
        return true;
    }
};

class SolutionBFS {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> colorArr(n, -1);

        for(int i = 0; i < n; i++) {
            if(colorArr[i] != -1) continue; // handle disconnected components

            queue<int> q;
            q.push(i);
            colorArr[i] = 0;

            while(!q.empty()) {
                int node = q.front(); q.pop();

                for(int neighbour : graph[node]) {
                    if(colorArr[neighbour] == -1) {
                        colorArr[neighbour] = 1 - colorArr[node]; // flip color
                        q.push(neighbour);
                    }
                    else if(colorArr[neighbour] == colorArr[node]) return false;
                }
            }
        }
        return true;
    }
};