#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

/*
-----------------------------------------
🎨 Painter's Partition Problem
-----------------------------------------

Approach:
- Binary Search on Answer
- Minimize the maximum workload assigned to a painter

Time Complexity:
- O(N * log(sum of boards))

Space Complexity:
- O(1)
-----------------------------------------
*/

class Solution {
public:
    bool possible(long long mid, int A, vector<int>& C) {
        int painters = 1;
        long long sum = 0;

        for (int i = 0; i < C.size(); i++) {
            if (sum + C[i] > mid) {
                painters++;
                sum = C[i];

                if (painters > A) return false;
            } else {
                sum += C[i];
            }
        }
        return true;
    }

    int paint(int A, int B, vector<int>& C) {
        long long mod = 10000003;

        long long low = *max_element(C.begin(), C.end());
        long long high = accumulate(C.begin(), C.end(), 0LL);

        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (possible(mid, A, C)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return (ans * B) % mod;
    }
};
