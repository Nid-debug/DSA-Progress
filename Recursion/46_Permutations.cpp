#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        permutation(nums, 0, result);
        return result;
    }

private:
    void permutation(vector<int>& nums, int idx, vector<vector<int>>& result) { 
        if(idx == nums.size()) {
            result.push_back(nums);
            return;
        }

        for(int i = idx; i < nums.size(); i++) {
            swap(nums[idx], nums[i]);
            permutation(nums, idx + 1, result);
            swap(nums[idx], nums[i]);
        }
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    
    vector<vector<int>> final = sol.permute(nums);

    for(const vector<int>& combination : final) {
        cout << "[ ";
        for(int num : combination) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}