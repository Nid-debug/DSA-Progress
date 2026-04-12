// Problem: Minimum Number of Days to Make m Bouquets
// Pattern: Binary Search on Answer

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
========================================
        Binary Search on Answer
========================================
Time Complexity: O(N * log(maxDay))
Space Complexity: O(1)
*/

class Solution {
public:
    bool canMake(vector<int>& bloomDay, int mid, int m, int k) {
        int bouquets = 0;
        int consecutive = 0;

        for (int i = 0; i < bloomDay.size(); i++) {
            if (bloomDay[i] <= mid) {
                consecutive++;

                if (consecutive == k) {
                    m--;
                    consecutive = 0;
                    if (m == 0) return true;
                }
            } 
            else {
                consecutive = 0;
            }
        }
        return false;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();

        // Early check 
        if ((long long)m * k > n) return -1;

        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canMake(bloomDay, mid, m, k)) {
                high = mid;  // Try smaller answer
            } 
            else {
                low = mid + 1;  // Need more days
            }
        }
        return low;
    }
};
