#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // Edge case: empty or single interval
        if (intervals.empty()) return {};
        
        // Sort intervals by start time
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); i++) {
            // If current interval overlaps with last merged interval
            if (intervals[i][0] <= result.back()[1]) {
                // Merge by updating the end of last interval
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                // No overlap, add current interval as new
                result.push_back(intervals[i]);
            }
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};

    vector<vector<int>> ans = sol.merge(intervals);

    for (auto &v : ans) {
        cout << "[" << v[0] << ", " << v[1] << "] ";
    }
    cout << endl;

    return 0; 
}