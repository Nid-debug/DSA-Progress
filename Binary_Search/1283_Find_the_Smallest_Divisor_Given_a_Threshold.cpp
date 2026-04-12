#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
========================================
    Binary Search on Answer
========================================
Problem: Find the Smallest Divisor Given a Threshold
Time Complexity: O(N * log(max(nums)))
Space Complexity: O(1)
*/

class Solution {
public:
    bool check(int mid, vector<int>& nums, int threshold) {
        long long sum = 0;

        for (int num : nums) {
            // ceil(num / mid)
            sum += ((long long)num + mid - 1) / mid;
        }

        return sum <= threshold;
    }  

    int smallestDivisor(vector<int>& nums, int threshold) {
        int low = 1;
        int high = *max_element(nums.begin(), nums.end());

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (check(mid, nums, threshold)) {
                high = mid;       // try smaller divisor
            } 
            else {
                low = mid + 1;    // need larger divisor
            }
        }
        return low;
    }
};