/*
    📚 Course Schedule II (Topological Sort - Kahn’s Algorithm)

    🔹 Problem:
    There are `numCourses` courses labeled from 0 to n-1.
    You are given prerequisites where:
        [a, b] means → to take course `a`, you must first complete `b`.

    Return an ordering of courses such that all prerequisites are satisfied.
    If it's not possible (cycle exists), return an empty array.

    🔹 Idea:
    - This is Topological Sorting of a directed graph
    - If a cycle exists → no valid ordering

    🔹 Approach (Kahn’s Algorithm - BFS):
    1. Build adjacency list
    2. Compute indegree of each node
    3. Push nodes with indegree = 0 into queue
    4. Process nodes and reduce indegree of neighbors
    5. Store order while processing

    🔹 Time Complexity: O(V + E)
    🔹 Space Complexity: O(V + E)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
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

        vector<int> completed;
        while(!q.empty()) {
            int node = q.front(); q.pop();
            completed.push_back(node);

            for(int neighbour : adj[node]) {
                indegree[neighbour]--;
                if(indegree[neighbour] == 0)
                    q.push(neighbour);
            }
        }
        if(completed.size() == numCourses) return completed;
        return {};
    }
};