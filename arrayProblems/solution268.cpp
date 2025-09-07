#include <bits/stdc++.h>
using namespace std;

class Solution {
public :
    int missingNumber(vector<int>& nums) {
    int n = nums.size();

    int expectedSum = 0;
    for (int i = 0; i <= n; i++) {
        expectedSum += i;  
    }
    int actualSum = 0;
    for (int x : nums) {
        actualSum += x;     
    }
    return expectedSum - actualSum;
  }
};

int main() {
    Solution s;
    vector<int> nums = {9,6,4,2,3,5,7,0,1};
    cout << s.missingNumber(nums) << endl;
}