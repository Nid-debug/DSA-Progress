/*
-----------------------------------------
📚 Book Allocation Problem
-----------------------------------------

Approach:
- Binary Search on Answer
- Minimize the maximum pages assigned to a student

Time Complexity:
- O(N * log(sum of pages))

Space Complexity:
- O(1)
-----------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    bool possible(int mid, vector<int> &arr, int k) {
        int students = 1;
        long long sum = 0;

        for (int i = 0; i < arr.size(); i++) {
            if (sum + arr[i] > mid) {
                students++;
                sum = arr[i];

                if (students > k) return false;
            } else {
                sum += arr[i];
            }
        }
        return true;
    }

    int findPages(vector<int> &arr, int k) {
        int n = arr.size();

        if (n < k) return -1;

        long long low = *max_element(arr.begin(), arr.end());
        long long high = accumulate(arr.begin(), arr.end(), 0LL);
        int ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (possible(mid, arr, k)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};