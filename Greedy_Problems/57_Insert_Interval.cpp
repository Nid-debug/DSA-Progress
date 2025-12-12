#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        int n = intervals.size();
        
        // Add all intervals that come before newInterval (no overlap)
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            i++;
        }
        
        // Merge all overlapping intervals with newInterval
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        result.push_back(newInterval);
        
        // Add all remaining intervals that come after newInterval
        while (i < n) {
            result.push_back(intervals[i]);
            i++;
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1,3}, {6,9}};
    vector<int> newInterval = {2,5};

    vector<vector<int>> ans = sol.insert(intervals, newInterval);

    for (auto &v : ans) {
        cout << "[" << v[0] << ", " << v[1] << "] ";
    }
    cout << endl;

    return 0; 
}