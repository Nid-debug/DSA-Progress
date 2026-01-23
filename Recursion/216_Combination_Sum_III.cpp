#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> current;
        match(k, n, 1, current, result);
        return result;
    }
    
private:
    void match(int k, int target, int start, vector<int>& current, vector<vector<int>>& result) {

        if (current.size() == k && target == 0) {
            result.push_back(current);
            return;
        }
        
        if (current.size() == k || target < 0) {
            return;
        }
        
        for (int i = start; i <= 9; i++) {

            if (i > target) break;
            
            current.push_back(i);
            
            match(k, target - i, i + 1, current, result);
            
            current.pop_back();
        }
    }
};

int main() {
    Solution sol;
    int k = 3;
    int n = 7;
    
    vector<vector<int>> final = sol.combinationSum3(k, n);

    for(const vector<int>& combination : final) {
        cout << "[ ";
        for(int num : combination) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}