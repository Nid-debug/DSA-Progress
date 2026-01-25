#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<int> subsetSums(vector<int>& nums) {
        vector<int> res;
        backtrack(nums, 0, 0, res);
        return res;
    }

  public:
    void backtrack(vector<int>& nums, int start, int sum, vector<int>& res) {
        res.push_back(sum);

        for(int i = start; i < nums.size(); i++) {
          backtrack(nums, i + 1, sum + nums[i], res);
        }
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 3};
    
    vector<int> final = sol.subsetSums(nums);

    for(int sum : final) {
       cout << sum << " ";
    }
    cout << endl;
    
    return 0;
}