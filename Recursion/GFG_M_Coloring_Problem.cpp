#include <iostream>
#include <vector>
using namespace std;

/**
 * Checks if it's safe to color vertex 'v' with color 'col'
 * by checking its adjacency list.
 */
bool isSafe(int v, const vector<vector<int>>& adj, vector<int>& color, int col) {
    for (int neighbor : adj[v]) {
        if (color[neighbor] == col) {
            return false;
        }
    }
    return true;
}

/**
 * Backtracking function to solve the M-Coloring problem.
 */
bool solve(int v, int n, int m, const vector<vector<int>>& adj, vector<int>& color) {
    // Base Case: All vertices are colored
    if (v == n) {
        return true;
    }

    // Try different colors from 1 to M
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, adj, color, c)) {
            color[v] = c; // Assign color

            // Recurse for the next vertex
            if (solve(v + 1, n, m, adj, color)) {
                return true;
            }

            // Backtrack: Remove color if it doesn't lead to a solution
            color[v] = 0;
        }
    }

    return false;
}

bool graphColoring(int n, int m, vector<pair<int, int>>& edges) {
    // Build Adjacency List
    vector<vector<int>> adj(n);
    for (auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    // Initialize all vertices with color 0 (no color)
    vector<int> color(n, 0);

    return solve(0, n, m, adj, color);
}

int main() {
    int N = 4; // Number of vertices
    int M = 2; // Number of colors
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};

    bool final = graphColoring(N, M, edges);
    cout << final << endl;
}