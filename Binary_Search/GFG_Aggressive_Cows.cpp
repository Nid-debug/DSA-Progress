#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
========================================
    Binary Search on Answer
========================================
Problem: Aggressive Cows
Time Complexity: O(N log N + N * log(maxDistance))
Space Complexity: O(1)
*/

class Solution {
public:
    bool possible(int mid, vector<int>& stalls, int k) {
        int cows = 1;                  // place first cow at first stall
        int lastPlaced = stalls[0];    // position of last placed cow

        for (int i = 1; i < stalls.size(); i++) {
            // check if we can place next cow
            if (stalls[i] - lastPlaced >= mid) {
                cows++;
                lastPlaced = stalls[i];

                if (cows == k) return true;  // early exit
            }
        }
        return false;
    }

    int aggressiveCows(vector<int>& stalls, int n, int k) {
        sort(stalls.begin(), stalls.end());

        int low = 1;
        int high = stalls[n - 1] - stalls[0];
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (possible(mid, stalls, k)) {
                ans = mid;       // store answer
                low = mid + 1;   // try larger distance
            } 
            else {
                high = mid - 1;  // reduce distance
            }
        }
        return ans;
    }
};