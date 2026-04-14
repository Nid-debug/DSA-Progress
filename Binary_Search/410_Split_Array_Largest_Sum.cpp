/*
-----------------------------------------
📚 Split Array Largest Sum
-----------------------------------------

Approach:
- Binary Search on Answer
- Minimize the maximum subarray sum

Time Complexity:
- O(N * log(sum of array))

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
        int num = 1;
        long long sum = 0;

        for (int i = 0; i < arr.size(); i++) {
            if (sum + arr[i] > mid) {
                num++;
                sum = arr[i];

                if (num > k) return false;
            } else {
                sum += arr[i];
            }
        }
        return true;
    }

    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();

        if (n < k) return -1;

        long long low = *max_element(nums.begin(), nums.end());
        long long high = accumulate(nums.begin(), nums.end(), 0LL);
        int ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (possible(mid, nums, k)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
