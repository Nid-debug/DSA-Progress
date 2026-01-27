#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        
        // IMPORTANT: Sort the array to group duplicates together
        sort(nums.begin(), nums.end());
        
        backtrack(nums, current, used, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, vector<int>& current, 
                   vector<bool>& used, vector<vector<int>>& result) {
        // Base case: if current permutation is complete
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            // Skip if already used
            if (used[i]) continue;
            
            // KEY: Skip duplicates
            // If current element equals previous element AND previous is not used,
            // skip to avoid duplicate permutations
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            
            // Choose
            current.push_back(nums[i]);
            used[i] = true;
            
            // Explore
            backtrack(nums, current, used, result);
            
            // Unchoose (backtrack)
            current.pop_back();
            used[i] = false;
        }
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    
    vector<vector<int>> final = sol.permuteUnique(nums);

    for(const vector<int>& combination : final) {
        cout << "[ ";
        for(int num : combination) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}