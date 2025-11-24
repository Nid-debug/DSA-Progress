#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int jumps = 0, farthest = 0, current_end = 0;

        // We don't need to jump from the last index
        for (int i = 0; i < nums.size() - 1; i++) {
            farthest = max(farthest, i + nums[i]);

            // When we reach the end of the current jump range
            if (i == current_end) {
                jumps++;
                current_end = farthest;
            }
        }
        return jumps;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 3, 1, 1, 4};

    cout << sol.jump(nums);  // Output: 2
    return 0;
}
