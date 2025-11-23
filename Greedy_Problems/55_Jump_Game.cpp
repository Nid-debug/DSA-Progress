#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reachable = 0;   

        for (int i = 0; i < nums.size(); i++) {
            if (i > reachable) return false;   
            reachable = max(reachable, i + nums[i]);  
        }
        return true;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {3, 2, 1, 0, 4};

    cout << sol.canJump(nums) << endl;  //Expected Output : 0
}