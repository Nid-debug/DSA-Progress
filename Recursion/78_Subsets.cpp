#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }

private:
    void backtrack(vector<int>& nums, int start, vector<int>& current, 
    vector<vector<int>>& result) {

        result.push_back(current);

        for(int i = start; i < nums.size(); i++) {
            current.push_back(nums[i]);
            backtrack(nums, i+1, current, result);
            current.pop_back();
        }
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    
    vector<vector<int>> final = sol.subsets(nums);

    for(const vector<int>& combination : final) {
        cout << "[ ";
        for(int num : combination) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}