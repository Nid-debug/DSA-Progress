#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
🚗 LeetCode 1094: Car Pooling 🧳

Problem:
You are given an array of trips where:
- trips[i][0] = Number of passengers.
- trips[i][1] = Pickup location.
- trips[i][2] = Drop-off location.

You are also given the vehicle's maximum capacity.

The vehicle moves only in one direction along a route.
Return true if it is possible to pick up and drop off all
passengers without exceeding the vehicle's capacity.
Otherwise, return false.

Approach: Greedy + Sorting + Min Heap

💡 Intuition:
We need to make sure that the number of passengers inside
the vehicle never exceeds its capacity.

The important observation is that passengers leave the
vehicle at their drop-off locations.

So, before picking up new passengers at a location, we must
first remove all passengers whose drop-off location has
already been reached.

We process trips in increasing order of their pickup locations.

To efficiently track when passengers leave, we use a Min Heap.

🔑 Key Idea:
Store the following information in the Min Heap: {drop-off location, number of passengers}

The Min Heap keeps the trip with the earliest drop-off
location at the top.

For every new trip:
1. Remove all trips whose drop-off location is <= current pickup.
2. Subtract their passengers from currPassengers.
3. Pick up the passengers of the current trip.
4. If currPassengers exceeds capacity, return false.
5. Otherwise, insert the current trip into the Min Heap.

Why do we use <= instead of < ?

If passengers are dropped off at location 5, and new
passengers are picked up at location 5, the dropped-off
passengers leave before the new passengers enter.

Therefore, their seats can be reused immediately.

🧠 Algorithm:
1. Sort trips by pickup location in ascending order.
2. Initialize:
   - currPassengers = 0
   - Min Heap to store {drop-off, passengers}
3. Traverse all trips:
   a. Extract passengers, pickup and drop-off locations.
   b. While the heap is not empty and its earliest
      drop-off location <= current pickup:
      - Subtract those passengers from currPassengers.
      - Remove that trip from the heap.
   c. Add the current trip's passengers.
   d. If currPassengers > capacity, return false.
   e. Push {drop-off location, passengers} into the heap.
4. If all trips are processed successfully, return true.

📌 Example:
trips = [[2, 1, 5], [3, 3, 7]]
capacity = 4

Trip 1: Pick up 2 passengers at 1, drop at 5.
- currPassengers = 2
- Heap = {(5, 2)}

Trip 2: Pick up 3 passengers at 3, drop at 7.
- Nobody has been dropped off yet.
- currPassengers = 2 + 3 = 5
- 5 > capacity (4)

Return false.

⏱️ Time Complexity: O(N log N)
- Sorting trips takes O(N log N).
- Each trip is pushed into the heap once.
- Each trip is removed from the heap once.
- Heap operations take O(log N).

💾 Space Complexity: O(N)
The Min Heap can store up to N trips.

🎯 Pattern to Remember:
Greedy + Sorting by Start Time + Min Heap

This pattern is useful for problems involving:
- Scheduling and resource allocation.
- Overlapping intervals.
- Tracking when resources become available.
- Checking whether a capacity limit is exceeded.

🔥 Important Insight:
When processing events in chronological order, use a Min Heap
to efficiently find which ongoing activities finish first.

For this problem:
- Pickup = Resource allocation.
- Drop-off = Resource release.
- Passengers currently inside = Resource usage.
- Capacity = Maximum available resources.
*/

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        
        sort(trips.begin(), trips.end(), [](auto& a, auto& b) {
            return a[1] < b[1];
        });

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;

        int currPassengers = 0;
        for(auto& trip : trips) {
            int passengers = trip[0], from = trip[1], to = trip[2];

            while(!minHeap.empty() && minHeap.top().first <= from) {
                currPassengers -= minHeap.top().second;
                minHeap.pop();
            }

            currPassengers += passengers;
            if(currPassengers > capacity) return false;
            
            minHeap.push({to, passengers});
        }
        return true;
    }
};