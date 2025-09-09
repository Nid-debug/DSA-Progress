// Problem: 2149. Rearrange Array Elements by Sign

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        int posIndex = 0;  // even indices for positives
        int negIndex = 1;  // odd indices for negatives

        for (int num : nums) {
            if (num > 0) {
                ans[posIndex] = num;
                posIndex += 2;
            } else {
                ans[negIndex] = num;
                negIndex += 2;
            }
        }
        return ans;
    }
};

// Example run
int main() {
    Solution sol;
    vector<int> nums = {3, 1, -2, -5, 2, -4};
    vector<int> result = sol.rearrangeArray(nums);

    cout << "Rearranged Array: ";
    for (int x : result) cout << x << " ";
    cout << endl;
    return 0;
}
