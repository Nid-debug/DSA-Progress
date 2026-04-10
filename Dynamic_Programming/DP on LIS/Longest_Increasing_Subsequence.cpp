#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int longestIncreasingSubsequence(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // dp[i] will store the length of LIS ending at index i
    vector<int> dp(n, 1);
    int maxLength = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLength = max(maxLength, dp[i]);
    }

    return maxLength;
}

int LISusingBinarySearch(vector<int>& nums) {
    if (nums.empty()) return 0;

    vector<int> temp;
    for (int x : nums) {
        // lower_bound finds the first element >= x using binary search
        auto it = lower_bound(temp.begin(), temp.end(), x);
        
        if (it == temp.end()) {
            // If x is greater than all current temp, extend the LIS
            temp.push_back(x);
        } else {
            // Otherwise, replace the tail element to keep it as small as possible
            *it = x;
        }
    }
    return temp.size();
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Length of LIS: " << longestIncreasingSubsequence(nums) << endl;
    cout << "Optimized LIS Length: " << LISusingBinarySearch(nums) << endl;
    return 0;
}