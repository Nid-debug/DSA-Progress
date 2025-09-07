#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;

        auto reverseArr = [&](int l, int r) {
            while (l < r) {
                swap(nums[l], nums[r]);
                l++, r--;
            }
        };
        reverseArr(0, n-1);     
        reverseArr(0, k-1);     
        reverseArr(k, n-1);     
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;
    s.rotate(nums, k);
    cout << "Rotated Array: ";
    for (int x : nums) {
        cout << x << " ";
    }
    cout << endl;
}