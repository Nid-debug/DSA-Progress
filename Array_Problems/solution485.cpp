#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 485: Max Consecutive Ones
----------------------------------
Given a binary array nums, return the maximum number of consecutive 1's in the array.

Example:
Input:  nums = [1,1,0,1,1,1]
Output: 3
*/

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int curr = 0, count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count = (nums[i] == 1) ? count + 1 : 0;
            curr = max(curr, count);
        }
        return curr;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,1,0,1,1,1};
    cout << s.findMaxConsecutiveOnes(nums) << endl; // Expected: 3
    return 0;
}
