#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 136: Single Number
----------------------------
Given a non-empty array of integers nums, every element appears twice except for one.
Find that single one.

Example:
Input:  nums = [4,1,2,1,2]
Output: 4
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num; // XOR cancels out duplicate numbers
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> nums = {4,1,2,1,2};
    cout << s.singleNumber(nums) << endl; // Expected: 4
    return 0;
}
