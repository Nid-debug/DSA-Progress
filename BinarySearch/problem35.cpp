#include <bits/stdc++.h>
using namespace std;

class Solution {
    public :
    int searchInsert(vector<int>& nums, int tar) {
        int st = 0, end = nums.size() - 1;

            while (st <= end) {
            int mid = st + (end - st) / 2;

            if (nums[mid] == tar) return mid;
            else if (nums[mid] < tar) st = mid + 1;
            else end = mid - 1;
        }
        return st;
    }
};


int main() {
    Solution s;
    vector<int> nums = {1, 3, 5, 6};
    int tar = 2;
    cout << s.searchInsert(nums, tar) << endl;
}