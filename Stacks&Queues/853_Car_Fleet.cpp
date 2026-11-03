#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/*
🏎️ Problem: Car Fleet

You are given:
- target: the destination position
- position[i]: the starting position of car i
- speed[i]: the speed of car i

All cars move toward the same target.
A car cannot pass another car. If a faster car catches a slower car,
they form a fleet and travel together at the slower car's speed.

Goal:
Return the number of car fleets that will arrive at the target.

-----------------------------------------------------

💡 Approach:

👉 Key Idea:
Sort cars by their starting positions in descending order.

Why?
- We process the car closest to the target first.
- Then we process cars behind it.
- We compare each car's arrival time with the fleet ahead.

-----------------------------------------------------

🧠 Step 1: Pair Positions and Speeds

Store each car as: {position, speed}

This keeps every car's position associated with its speed.

-----------------------------------------------------

🧠 Step 2: Sort in Descending Position Order

Cars are now processed from closest to the target
to farthest from the target.

-----------------------------------------------------

🧠 Step 3: Calculate Arrival Time

For each car: time = (target - position) / speed

This is the time the car would take to reach the target
if it did not catch another car.

-----------------------------------------------------

🧠 Step 4: Identify Fleets Using a Stack

For each car:

1. If the stack is empty:
   - Push its arrival time.
   - It forms a new fleet.

2. If its arrival time is greater than the time
   of the fleet ahead:
   - It cannot catch that fleet before the target.
   - Push its time because it forms a new fleet.

3. Otherwise:
   - Its arrival time is less than or equal to the
     fleet ahead's time.
   - It catches up and joins that fleet.
   - Do not push its time.

Finally: stack.size() = number of fleets

-----------------------------------------------------

⚠️ Key Insight:

If a car behind would arrive earlier than or at the
same time as the fleet ahead, it cannot pass that fleet.

Therefore, it joins the fleet instead of forming a new one.

-----------------------------------------------------

⏱ Time Complexity:

- Pairing cars: O(N)
- Sorting cars: O(N log N)
- Processing cars: O(N)

Total: O(N log N)

-----------------------------------------------------

📦 Space Complexity:

- Cars array: O(N)
- Stack: O(N)

Total: O(N)

-----------------------------------------------------

🎯 Pattern:

Car Fleet
    ↓
Sorting + Greedy
    ↓
Arrival Time Comparison
    ↓
Monotonic Stack

The stack stores fleet arrival times in increasing order
from the fleet closest to the target to fleets behind it.
*/

class Solution
{
public:
    int carFleet(int target, vector<int> &position, vector<int> &speed)
    {
        int n = position.size();

        vector<pair<int, int>> cars(n);
        for (int i = 0; i < n; i++)
            cars[i] = {position[i], speed[i]};

        sort(cars.rbegin(), cars.rend());

        stack<double> st;

        for (auto &[pos, spd] : cars)
        {
            double time = (double)(target - pos) / spd;

            if (st.empty() || time > st.top())
                st.push(time);
        }

        return st.size();
    }
};