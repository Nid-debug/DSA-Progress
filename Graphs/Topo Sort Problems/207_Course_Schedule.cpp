/*
    📚 Course Schedule (Topological Sort - Kahn’s Algorithm)

    🔹 Problem:
    There are `numCourses` courses labeled from 0 to n-1.
    You are given prerequisites where:
        [a, b] means → to take course `a`, you must first complete `b`.

    Return true if you can finish all courses, else false.

    🔹 Idea:
    - This is a cycle detection problem in a directed graph
    - If there is a cycle → impossible to complete all courses

    🔹 Approach (Kahn’s Algorithm - BFS):
    1. Build adjacency list
    2. Compute indegree of each node
    3. Push nodes with indegree = 0 into queue
    4. Process nodes and reduce indegree of neighbors
    5. Count processed nodes

    🔹 Time Complexity: O(V + E)
    🔹 Space Complexity: O(V + E)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        // build adjacency list and indegree array
        for(auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
            indegree[pre[0]]++;
        }

        // push all courses with no prerequisites
        queue<int> q;
        for(int i = 0; i < numCourses; i++)
            if(indegree[i] == 0) q.push(i);

        int completed = 0;
        while(!q.empty()) {
            int node = q.front(); q.pop();
            completed++;

            for(int neighbour : adj[node]) {
                indegree[neighbour]--;
                if(indegree[neighbour] == 0)
                    q.push(neighbour);
            }
        }
        return completed == numCourses; // if all courses completed, no cycle
    }
};

