#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    const int MOD = 1e9 + 7;
    int recurse(vector<int> &arr, int idx, int target, vector<vector<int>> &dp)
    {
        if (idx == 0)
        {
            if (target == 0 && arr[0] == 0)
                return 2; // both include & exclude
            if (target == 0)
                return 1; // exclude arr[0]
            if (target == arr[0])
                return 1; // include arr[0]
            return 0;
        }
        if (dp[idx][target] != -1)
            return dp[idx][target];

        int notTake = recurse(arr, idx - 1, target, dp);
        int take = 0;
        if (arr[idx] <= target)
            take = recurse(arr, idx - 1, target - arr[idx], dp);

        return dp[idx][target] = (take + notTake) % MOD;
    }

    int countPartitions(vector<int> &arr, int diff)
    {
        int totalSum = 0;
        for (int x : arr)
            totalSum += x;
        if ((totalSum + diff) % 2 != 0 || (totalSum + diff) < 0)
            return 0;
        int target = (totalSum + diff) / 2;
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        return recurse(arr, n - 1, target, dp);
    }
};

class SolutionTab
{
public:
    const int MOD = 1e9 + 7;
    int countTab(vector<int> &arr, int diff)
    {
        int totalSum = 0;
        for (int x : arr)
            totalSum += x;
        if ((totalSum + diff) % 2 != 0 || (totalSum + diff) < 0)
            return 0;
        int target = (totalSum + diff) / 2;
        int n = arr.size();

        // dp[i][j] = number of subsets using first i elements with sum j
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        // Base case: idx = 0
        if (arr[0] == 0)
            dp[0][0] = 2; // include or exclude 0
        else
        {
            dp[0][0] = 1; // exclude arr[0]
            if (arr[0] <= target)
                dp[0][arr[0]] = 1; // include arr[0]
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= target; j++)
            {
                int notTake = dp[i - 1][j];
                int take = 0;
                if (arr[i] <= j)
                    take = dp[i - 1][j - arr[i]];
                dp[i][j] = (take + notTake) % MOD;
            }
        }

        return dp[n - 1][target];
    }
};

class SolutionSpace
{
public:
    const int MOD = 1e9 + 7;
    int countTab(vector<int> &arr, int diff)
    {
        int totalSum = 0;
        for (int x : arr)
            totalSum += x;
        if ((totalSum + diff) % 2 != 0 || (totalSum + diff) < 0)
            return 0;
        int target = (totalSum + diff) / 2;
        int n = arr.size();

        // dp[i][j] = number of subsets using first i elements with sum j
        vector<int> prev(target + 1), curr(target + 1, 0);

        // Base case: idx = 0
        if (arr[0] == 0)
            prev[0] = 2; // include or exclude 0
        else
        {
            prev[0] = 1; // exclude arr[0]
            if (arr[0] <= target)
                prev[arr[0]] = 1; // include arr[0]
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= target; j++)
            {
                int notTake = prev[j];
                int take = 0;
                if (arr[i] <= j)
                    take = prev[j - arr[i]];
                curr[j] = (take + notTake) % MOD;
            }
            prev = curr;
        }
        return prev[target];
    }
};

int main()
{
    Solution sol;
    SolutionTab tab;
    SolutionSpace spa;
    vector<int> arr = {1, 1, 2, 3};
    int diff = 1;
    cout << sol.countPartitions(arr, diff) << endl;
    cout << tab.countTab(arr, diff) << endl;
    cout << spa.countTab(arr, diff) << endl;
    return 0;
}