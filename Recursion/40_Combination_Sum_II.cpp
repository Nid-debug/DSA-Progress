#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void combination(int idx, int target, vector<int>& candidates, 
        vector<int>& ds, vector<vector<int>>& ans) {
        if(target == 0) {
            ans.push_back(ds);
            return;
        }
        
        for(int i = idx; i < candidates.size(); i++) {
            if(i > idx && candidates[i] == candidates[i-1]) continue;
            
            if(candidates[i] > target) break;
            ds.push_back(candidates[i]);
            
            combination(i + 1, target - candidates[i], candidates, ds, ans);
            ds.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> ds;
        
        sort(candidates.begin(), candidates.end());
        
        combination(0, target, candidates, ds, ans);
        
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;
    
    vector<vector<int>> final = sol.combinationSum2(candidates, target);

    for(const vector<int>& combination : final) {
        cout << "[ ";
        for(int num : combination) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}