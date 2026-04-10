/*
    Problem: Longest Bitonic Subsequence

    A bitonic subsequence is:
    Increasing → then Decreasing

    Idea:
    - lis[i]  = LIS ending at i (left to right)
    - lds[i]  = LIS starting from i (right to left)

    Answer:
    max(lis[i] + lds[i] - 1)

    Time Complexity: O(n^2)
    Space Complexity: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

int longestBitonicSubsequence(vector<int>& nums) {

    int n = nums.size();

    vector<int> lis(n, 1); // increasing
    vector<int> lds(n, 1); // decreasing

    // LIS (left → right)
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (nums[prev] < nums[i] && lis[prev] + 1 > lis[i]) {

                lis[i] = lis[prev] + 1;
            }
        }
    }

    // LDS (right → left)
    for (int i = n - 1; i >= 0; i--) {
        for (int next = n - 1; next > i; next--) {
            if (nums[next] < nums[i] && lds[next] + 1 > lds[i]) {

                lds[i] = lds[next] + 1;
            }
        }
    }

    int maxi = 0;
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, lis[i] + lds[i] - 1);
    }
    return maxi;
}


int main() {
    vector<int> nums = {1, 2, 5, 3, 2};
    cout << "Longest Bitonic Subsequence Length: " << longestBitonicSubsequence(nums) << endl;
    return 0;
}