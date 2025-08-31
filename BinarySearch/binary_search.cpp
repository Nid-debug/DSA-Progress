#include <bits/stdc++.h>
using namespace std;

class Solution {
    public :
    int search(vector<int>& nums, int tar) {
        int n = nums.size();
        int start = 0, end = n-1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] == tar) return mid;
            else if (nums[mid] > tar) {
                end = mid - 1;
            }
            else start = mid + 1;
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int tar = 9;
    cout << s.search(nums, tar) << endl;
}