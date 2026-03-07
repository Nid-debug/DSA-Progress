#include <iostream>
#include <vector>
using namespace std;

class SolutionMemo {
private:
    bool solve(int index, int target, vector<int>& arr, vector<vector<int>>& dp) {
        // Base case: target achieved
        if (target == 0) return true;
        
        // Base case: no more elements
        if (index == 0) return arr[0] == target;  // Check if last element equals target

        if(dp[index][target] != -1) return dp[index][target];
        
        // Choice 1: Include current element (if it doesn't exceed target)
        bool include = false;
        if (arr[index] <= target) {
            include = solve(index - 1, target - arr[index], arr, dp);
        }
        
        // Choice 2: Exclude current element
        bool exclude = solve(index - 1, target, arr, dp);
        
        // Return true if either choice works
        return dp[index][target] = (include || exclude);
    }
    
public:
    bool isSubsetSum(int n, int target, vector<int>& arr) {
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        return solve(n - 1, target, arr, dp);
    }
};

class SolutionTab {
public:
    bool isSubsetSum(int n, int target, vector<int>& arr) {
        // dp[index][target]
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        // Base Case 1: Target 0 is always possible (by picking empty subset)
        for(int i = 0; i < n; i++) dp[i][0] = true;

        // Base Case 2: First element can form a subset if it's <= target
        if(arr[0] <= target) dp[0][arr[0]] = true;

        for(int idx = 1; idx < n; idx++) {
            for(int tar = 1; tar <= target; tar++) {
                
                // Option 1: Don't pick the current element
                bool exclude = dp[idx - 1][tar];
                
                // Option 2: Pick the current element (if it fits)
                bool include = false;
                if (arr[idx] <= tar) {
                    include = dp[idx - 1][tar - arr[idx]];
                }

                dp[idx][tar] = include || exclude;
            }
        }
        return dp[n - 1][target];
    }
};

class SolutionSpace {
public:
    bool isSubsetSum(int n, int target, vector<int>& arr) {
        vector<bool> prev(target + 1, false);

        // Base Case 1: Target 0 is always possible
        prev[0] = true;

        // Base Case 2: First element
        if(arr[0] <= target) prev[arr[0]] = true;

        for(int idx = 1; idx < n; idx++) {
            // We need a current row to store results without overwriting prev too early
            vector<bool> curr(target + 1, false);
            curr[0] = true; // Target 0 is always possible
            
            for(int tar = 1; tar <= target; tar++) {
                bool exclude = prev[tar];

                bool include = false;
                if (arr[idx] <= tar) {
                    include = prev[tar - arr[idx]];
                }
                
                curr[tar] = include || exclude;
            }
            prev = curr; // Move to the next row
        }
        return prev[target];
    }
};

int main() {
    SolutionMemo sol;
    SolutionTab tab;
    SolutionSpace spa;

    vector<int> arr = {1, 2, 7, 3};
    int target = 10;

    int n = arr.size();
    cout << sol.isSubsetSum(n, target, arr) << endl;
    cout << tab.isSubsetSum(n, target, arr) << endl;
    cout << spa.isSubsetSum(n, target, arr) << endl;

    return 0;
}