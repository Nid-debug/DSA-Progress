#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isSubsetSum(int n, int target, vector<int>& arr) {
        vector<bool> prev(target + 1, false);

        prev[0] = true;

        if(arr[0] <= target) prev[arr[0]] = true;

        for(int idx = 1; idx < n; idx++) {
            vector<bool> curr(target + 1, false);
            curr[0] = true; 
            
            for(int tar = 1; tar <= target; tar++) {
                bool exclude = prev[tar];

                bool include = false;
                if (arr[idx] <= tar) {
                    include = prev[tar - arr[idx]];
                }
                
                curr[tar] = include || exclude;
            }
            prev = curr; 
        }
        return prev[target];
    }

    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int totSum = 0;
        for(int i = 0; i < n; i++) totSum += nums[i];
        if(totSum % 2) return false;
        int target = totSum / 2;

        return isSubsetSum(n, target, nums);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 5, 11, 5};
    cout << sol.canPartition(nums) << endl;
    return 0;
}

