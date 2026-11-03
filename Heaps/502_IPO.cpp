#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
💰 LeetCode 502: IPO

Problem:
You are given:
- k: Maximum number of projects you can complete.
- w: Initial capital.
- profits[i]: Profit earned from completing project i.
- capital[i]: Minimum capital required to start project i.

You can complete at most k projects, and after completing a
project, its profit is added to your available capital.

Return the maximum capital you can obtain after completing
at most k projects.

🧠 Approach: Greedy + Sorting + Max Heap

Intuition:
At any point, we can only choose projects whose required
capital is less than or equal to our current capital.

Among all currently affordable projects, we should choose
the one with the maximum profit.

This is a greedy strategy because selecting the most
profitable available project increases our capital as much
as possible, potentially unlocking even more projects.

📊 Key Idea:
Use two data structures:

1. Sorted vector of projects:
   Store each project as {required capital, profit} and sort
   by required capital in ascending order.

2. Max heap (priority_queue):
   Store the profits of all projects we can currently afford.
   The largest profit will always be at the top.

🧠 Algorithm:
1. Combine capital[i] and profits[i] into project pairs.
2. Sort projects by required capital.
3. Initialize an index i = 0 and an empty max heap.
4. Repeat at most k times:
   a. Add every project with required capital <= w
      to the max heap.
   b. If the heap is empty, stop because no project
      is currently affordable.
   c. Select the project with the maximum profit.
   d. Add its profit to w and remove it from the heap.
5. Return w.

Example:
k = 2, w = 0
profits = [1, 2, 3]
capital = [0, 1, 1]

Initially:
Capital = 0
Affordable projects: profit 1
Choose profit 1 -> Capital = 1

Now:
Affordable projects: profit 2 and profit 3
Choose profit 3 -> Capital = 4

Final answer = 4

⏱ Time Complexity: O(N log N + K log N)
- Sorting all projects takes O(N log N).
- Each project enters the heap at most once, taking
  O(N log N) overall.
- Each selected project is removed from the heap in
  O(log N), up to K times.
- Total: O(N log N + K log N), where N is the number
  of projects.

📦 Space Complexity: O(N)
The project vector and max heap can each store O(N) elements.

⚠️ Pattern to Remember:
Greedy + Sorting + Max Heap

When you must repeatedly choose the maximum-value option
among items that satisfy a changing eligibility condition:
1. Sort items by when they become eligible.
2. Add eligible items to a max heap.
3. Greedily select the maximum-value item.
*/

class Solution
{
public:
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        vector<pair<int, int>> projects;

        for (int i = 0; i < profits.size(); i++)
        {
            projects.push_back({capital[i], profits[i]});
        }

        sort(projects.begin(), projects.end());

        priority_queue<int> pq;
        int i = 0;
        int n = projects.size();

        while (k--)
        {
            while (i < n && projects[i].first <= w)
            {
                pq.push(projects[i].second);
                i++;
            }

            if (pq.empty())
                break;

            w += pq.top();
            pq.pop();
        }

        return w;
    }
};