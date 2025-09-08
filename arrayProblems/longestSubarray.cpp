#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubarrayWithSumK(vector<int>& nums, int k) {
        unordered_map<int, int> mp; // prefixSum -> first index
        int sum = 0, maxLen = 0;

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];

            if (sum == k)  // subarray from start
                maxLen = max(maxLen, i + 1);

            if (mp.find(sum - k) != mp.end()) {
                int len = i - mp[sum - k];
                maxLen = max(maxLen, len);
            }

            // store only the first occurrence of prefix sum
            if (mp.find(sum) == mp.end())
                mp[sum] = i;
        }

        return maxLen;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 1, 1, 1, 1, 4, 2, 3}; // Expected : 4
    int k = 6;

    cout << sol.longestSubarrayWithSumK(nums, k) << endl;
    return 0;
}