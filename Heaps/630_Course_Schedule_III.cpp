#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
📚 LeetCode 630: Course Schedule III 🎓

Problem:
You are given an array of courses where:
- courses[i][0] = Duration of the course.
- courses[i][1] = Last day by which the course must be completed.

You can take only one course at a time, and you must complete
a course before or on its deadline.

Return the maximum number of courses you can take.

Approach: Greedy + Sorting + Max Heap

💡 Intuition:
We want to complete as many courses as possible.

The important observation is that we should consider courses
in increasing order of their deadlines.

Why sort by deadline?
Courses with earlier deadlines are more urgent, so we should
consider them first.

However, simply accepting every course that fits is not
always optimal.

Suppose we have already selected some courses, and a new
course cannot fit within its deadline.

Instead of immediately rejecting it, we can check whether
replacing a previously selected longer course with this
shorter course would help.

This is where the Max Heap comes in.

🔑 Key Idea:
Maintain a max heap containing the durations of all selected
courses.

The heap's top always gives us the longest selected course.

For every course:
1. If it fits, accept it.
2. Otherwise, if the longest selected course takes more time
   than the current course, replace that longer course.

By doing this, we reduce the total time while keeping the
number of selected courses unchanged.

🧠 Algorithm:
1. Sort all courses by their deadlines in ascending order.
2. Initialize:
   - totTime = 0
   - maxHeap = empty max heap
3. Traverse every course:
   a. Extract its duration and deadline.
   b. If totTime + duration <= deadline:
      - Add its duration to totTime.
      - Push its duration into the max heap.
   c. Otherwise, check whether the heap is non-empty and
      its maximum duration is greater than the current one.
      - Remove the longest selected course.
      - Subtract its duration from totTime.
      - Add the current course instead.
      - Push the current duration into the heap.
4. Return the size of the max heap.

📌 Example:
courses = [[100, 200], [200, 1300],
           [1000, 1250], [2000, 3200]]

After sorting by deadline, process:

Course [100, 200]:
- Total time = 100
- Heap = [100]

Course [200, 1300]:
- Total time = 300
- Heap = [200, 100]

Course [1000, 1250]:
- Total time would become 1300, which exceeds 1250.
- Longest selected course = 200.
- Replace 200 with 1000? No, because 200 is shorter.
- Reject this course.

Course [2000, 3200]:
- Total time would become 2300, which fits.
- Accept it.

Final selected courses = 3.

⏱️ Time Complexity: O(N log N)
- Sorting takes O(N log N).
- Each course is pushed into the heap at most once.
- Each heap operation takes O(log N).

💾 Space Complexity: O(N)
The max heap can store up to N course durations.

🎯 Pattern to Remember:
Greedy + Sorting by Deadline + Max Heap

Whenever you need to maximize the number of selected tasks
under deadlines:
- Sort by deadline.
- Track the total time.
- Use a max heap to remove the most expensive selected task
  when the current task cannot fit.

🔥 Important Insight:
When a new course doesn't fit, don't always reject it.
Replacing the longest previously selected course with the
current shorter course can preserve the number of courses
while freeing up time for future courses.
*/

class Solution
{
public:
    int scheduleCourse(vector<vector<int>> &courses)
    {
        int n = courses.size();

        sort(courses.begin(), courses.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });

        priority_queue<int> maxHeap;
        int totTime = 0;

        for (int i = 0; i < n; i++)
        {
            int dur = courses[i][0];
            int lastDay = courses[i][1];

            if (totTime + dur <= lastDay)
            {
                totTime += dur;
                maxHeap.push(dur);
            }

            else if (!maxHeap.empty() && maxHeap.top() > dur)
            {
                totTime -= maxHeap.top();
                maxHeap.pop();

                totTime += dur;
                maxHeap.push(dur);
            }
        }
        return maxHeap.size();
    }
};