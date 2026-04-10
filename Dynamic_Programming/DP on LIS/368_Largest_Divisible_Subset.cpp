#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> largestDivisibleSubset(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {};

    // Sort to handle divisibility easily (only check nums[i] % nums[j])
    sort(nums.begin(), nums.end());

    vector<int> dp(n, 1);      // Stores length of largest subset ending at i
    vector<int> parent(n, -1); // Stores previous index to reconstruct path
    int maxIdx = 0;            // Track index of the overall largest subset tail

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // If nums[i] is divisible by nums[j] and improves the subset length
            if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        // Update the global maximum index
        if (dp[i] > dp[maxIdx]) {
            maxIdx = i;
        }
    }

    // Reconstruct the subset using the parent pointers
    vector<int> result;
    int curr = maxIdx;
    while (curr != -1) {
        result.push_back(nums[curr]);
        curr = parent[curr];
    }
    return result;
}

int main() {
    vector<int> nums = {1, 2, 4, 8};
    vector<int> result = largestDivisibleSubset(nums);

    cout << "Largest Divisible Subset: ";
    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}