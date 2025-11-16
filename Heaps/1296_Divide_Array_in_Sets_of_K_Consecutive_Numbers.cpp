#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Time: O(n log n) because of sorting
// Space: O(n) for the frequency map

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.size() % k != 0) return false;

        map<int, int> freq; // ordered map keeps keys sorted
        for (int x : nums) {
            freq[x]++;
        }

        // Try to build sequences starting from smallest key
        while (!freq.empty()) {
            int start = freq.begin()->first; // smallest number available

            // Try to form a sequence of length k starting from 'start'
            for (int i = 0; i < k; i++) {
                int num = start + i;

                if (freq[num] == 0) return false; // missing number → can't form group

                freq[num]--;

                if (freq[num] == 0) {
                    freq.erase(num);
                }
            }
        }
        return true;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 6};
    int k = 4;
    cout << sol.isPossibleDivide(nums, k) << endl; // Output: 1
    return 0;
}