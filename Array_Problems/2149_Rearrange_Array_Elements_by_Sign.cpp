// Problem: 2149. Rearrange Array Elements by Sign
// Time Complexity = O(N)
// Space Complexity = O(N)

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