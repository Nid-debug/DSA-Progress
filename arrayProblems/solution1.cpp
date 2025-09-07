#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Map to store numbers we've seen so far and their indices
        unordered_map<int, int> mp; // key: number, value: index

        // Iterate through each number in the array
        for (int i = 0; i < nums.size(); ++i) {
            int need = target - nums[i]; // The number we need to form the target

            // If we have already seen the required number, return the pair of indices
            if (mp.count(need)) {
                return {mp[need], i};
            }

            // Otherwise, store the current number with its index
            mp[nums[i]] = i;
        }

        // Return empty vector if no solution is found
        return {};
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> result = sol.twoSum(nums, target);

    cout << "Indices: ";
    for (int idx : result) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
