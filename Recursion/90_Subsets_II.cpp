// LeetCode 90 - Subsets II
// Approach: Backtracking + Sorting + Duplicate Skipping
// Time Complexity: O(2^n) (all possible subsets)
// Space Complexity: O(n) recursion depth (excluding output)

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> curr;                 // Current subset being built
        vector<vector<int>> result;       // Stores all unique subsets
        
        sort(nums.begin(), nums.end());   // Sort to group duplicates together

        backtrack(nums, 0, curr, result); // Start backtracking from index 0
        return result;
    }

private:
    void backtrack(vector<int>& nums, int start, vector<int>& curr, vector<vector<int>>& result) {

        // Every state of 'curr' is a valid subset, so store it
        result.push_back(curr);

        // Explore all choices starting from index 'start'
        for(int i = start; i < nums.size(); i++) {

            // Skip duplicates:
            // If current element is same as previous one and not at the start of this recursion level,
            // then skipping it avoids generating duplicate subsets
            if(i > start && nums[i] == nums[i - 1]) {
                continue;
            }

            // Choose the current element
            curr.push_back(nums[i]);

            // Recurse for the next index
            backtrack(nums, i + 1, curr, result);

            // Undo the choice (backtrack)
            curr.pop_back();
        }
    }
};
