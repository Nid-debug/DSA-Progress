/*
🏙️ Problem: Find the City With the Smallest Number of Neighbors at a Threshold Distance

Given:
- n cities (0 to n-1)
- weighted edges between cities
- a distanceThreshold

Goal:
Find the city with the smallest number of cities reachable
within distanceThreshold.

If multiple cities have same count → return the city with the largest index.

-----------------------------------------------------

💡 Approach (Floyd-Warshall):

1. We need shortest distance between ALL pairs → use Floyd-Warshall.
2. Initialize distance matrix:
   - dist[i][j] = edge weight if exists
   - dist[i][i] = 0
   - else INF

3. Run Floyd-Warshall:
   - Try every node as an intermediate (via)
   - Update shortest paths

4. For each city:
   - Count how many cities are reachable within threshold

5. Return city with:
   - minimum reachable count
   - if tie → larger index

-----------------------------------------------------

⚠️ Key Idea:
- This is an "All-Pairs Shortest Path" problem
- Floyd-Warshall is perfect when n is small (~100)

-----------------------------------------------------

⏱ Time Complexity:
- Floyd-Warshall: O(n³)
- Counting: O(n²)
=> Overall: O(n³)

📦 Space Complexity:
- Distance matrix: O(n²)
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        for(int i = 0; i < n; i++) dist[i][i] = 0;

        for(auto& edge : edges) {
            dist[edge[0]][edge[1]] = edge[2];
            dist[edge[1]][edge[0]] = edge[2];
        }

        for(int via = 0; via < n; via++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(dist[i][via] == 1e9 || dist[via][j] == 1e9) continue;
                    dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j]);
                }
            }
        }

        int resultCity = -1, minCount = n;
        for(int city = 0; city < n; city++) {
            int count = 0;
            for(int j = 0; j < n; j++) {
                if(city != j && dist[city][j] <= distanceThreshold) count++;
            }

            if(count <= minCount) {
                minCount = count;
                resultCity = city;
            }
        }
        return resultCity;
    }
};