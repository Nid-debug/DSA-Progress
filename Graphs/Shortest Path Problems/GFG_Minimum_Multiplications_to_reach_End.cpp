/*
🔢 Problem: Minimum Multiplications to Reach End

Given:
- An array of numbers (arr)
- A start value
- A target value (end)

You can:
- Multiply current number with any element from arr
- Take modulo 1000 after multiplication

Goal:
Find the minimum number of steps to reach 'end' from 'start'

-----------------------------------------------------

💡 Approach:
1. Treat each number (0 → 999) as a node in a graph.
2. From each node, you can go to:
   (node * arr[i]) % 1000
3. Since all operations cost 1 → use BFS.
4. Use distance array to track minimum steps.

-----------------------------------------------------

⚠️ Key Observations:
- State space is limited → only 1000 nodes (0 to 999)
- BFS guarantees shortest path in unweighted graph

-----------------------------------------------------

⏱ Time Complexity:
- For each node, we try all elements in arr
=> O(1000 * N)

📦 Space Complexity:
- Distance array: O(1000)
- Queue: O(1000)
=> Overall: O(1000)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
  public:
    int minSteps(vector<int>& arr, int start, int end) {
        if(start == end) return 0;

        int mod = 1000;
        vector<int> dist(mod, 1e9);
        dist[start] = 0;

        queue<int> q;
        q.push(start);

        int steps = 0;

        while(!q.empty()) {
            int size = q.size();
            steps++;

            for(int i = 0; i < size; i++) {
                int node = q.front(); q.pop();

                for(int num : arr) {
                    int newNum = (node * num) % mod;

                    if(newNum == end) return steps;

                    if(dist[newNum] == 1e9) {
                        dist[newNum] = steps;
                        q.push(newNum);
                    }
                }
            }
        }
        return -1;
    }
};