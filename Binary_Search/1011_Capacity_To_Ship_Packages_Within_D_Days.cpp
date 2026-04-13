#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

/*
========================================
    Binary Search on Answer
========================================
Problem: Capacity to Ship Packages Within D Days
Time Complexity: O(N * log(sum(weights)))
Space Complexity: O(1)
*/

class Solution {
public:
    bool possible(long long mid, vector<int>& weights, int days) {
        int daysNeeded = 1;
        long long sum = 0;

        for (int i = 0; i < weights.size(); i++) {
            if (sum + weights[i] > mid) {
                daysNeeded++;
                sum = 0;
            }
            sum += weights[i];
        }
        return daysNeeded <= days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        long long low = *max_element(weights.begin(), weights.end());
        long long high = accumulate(weights.begin(), weights.end(), 0LL);

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (possible(mid, weights, days)) {
                high = mid;        // try smaller capacity
            } 
            else {
                low = mid + 1;     // need more capacity
            }
        }
        return low;
    }
};