/*
    Problem: Number of Longest Increasing Subsequences
    Link: https://leetcode.com/problems/number-of-longest-increasing-subsequence/

    Approach:
    - dp[i]  → length of LIS ending at index i
    - cnt[i] → number of LIS ending at index i

    Logic:
    - If we find a longer subsequence → update dp and copy count
    - If we find another subsequence of same length → add count

    Time Complexity: O(n^2)
    Space Complexity: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {

        int n = nums.size();
        vector<int> dp(n, 1);    // length of LIS
        vector<int> cnt(n, 1);   // count of LIS

        int maxi = 1;

        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++) {

                if (nums[i] > nums[prev] && 1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                    cnt[i] = cnt[prev];
                }
                else if (nums[i] > nums[prev] && 1 + dp[prev] == dp[i]) {
                    cnt[i] += cnt[prev];
                }
            }
            maxi = max(maxi, dp[i]);
        }

        int nos = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] == maxi) nos += cnt[i];
        }
        return nos;
    }
};


int main() {
    Solution sol;
    vector<int> nums = {2, 2, 2, 2, 2};
    cout << "Number of LIS: " << sol.findNumberOfLIS(nums) << endl;
    return 0;
}