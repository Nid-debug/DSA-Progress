#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int solve(vector<int> &arr, int target)
    {

        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        for (int i = 0; i < n; i++)
            dp[i][0] = 1;

        if (arr[0] <= target)
            dp[0][arr[0]] = 1;

        for (int j = 1; j < n; j++)
        {
            for (int sum = 0; sum <= target; sum++)
            {
                int notPick = dp[j - 1][sum];

                int pick = 0;
                if (arr[j] <= sum)
                {
                    pick = dp[j - 1][sum - arr[j]];
                }
                dp[j][sum] = notPick + pick;
            }
        }
        return dp[n - 1][target];
    }
};

class SolutionSpace
{
public:
    int solve(vector<int> &arr, int target)
    {
        int n = arr.size();
        vector<int> dp(target + 1, 0);

        dp[0] = 1; // Base case: sum of 0 is always possible (empty set)

        for (int i = 0; i < n; i++)
        {
            // Iterate backwards to ensure we use the 'prev' row's values
            for (int sum = target; sum >= arr[i]; sum--)
            {
                dp[sum] = dp[sum] + dp[sum - arr[i]];
            }
        }
        return dp[target];
    }
};

int main()
{
    Solution sol;
    SolutionSpace spa;
    vector<int> arr = {1, 2, 3, 4, 5};
    int target = 4;
    cout << sol.solve(arr, target) << endl;
    cout << spa.solve(arr, target) << endl;
    return 0;
}