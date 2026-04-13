#include <iostream>
#include <vector>
using namespace std;

/*
========================================
    Brute Force Approach
========================================
Time Complexity: O(N + K)
Space Complexity: O(1)
*/

class SolutionBrute {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int missingCount = 0;
        int current = 0;
        int i = 0;

        while (missingCount < k) {
            current++;

            if (i < arr.size() && arr[i] == current) {
                i++;
            } 
            else {
                missingCount++;
            }
        }
        return current;
    }
};

/*
========================================
    Binary Search Approach
========================================
Time Complexity: O(log N)
Space Complexity: O(1)
*/

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int lo = 0;
        int hi = arr.size();

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            // Missing numbers till index mid
            if (arr[mid] - mid - 1 >= k) {
                hi = mid;
            } 
            else {
                lo = mid + 1;
            }
        }
        return lo + k;
    }
};