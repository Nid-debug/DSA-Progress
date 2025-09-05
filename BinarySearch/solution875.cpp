#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long hoursNeeded(vector<int>& piles, int k, int h) {
    long long hours = 0;
    for (int pile : piles) {
        hours += (pile + k - 1) / k; 
        if (hours > h) return hours;
    }
    return hours;
}

    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1, high = *max_element(piles.begin(), piles.end());
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hoursNeeded(piles, mid, h) <= h) {
                ans = mid;         
                high = mid - 1;   
            } else {
                low = mid + 1;    
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> piles = {30,11,23,4,20};
    int h = 6;
    cout << s.minEatingSpeed(piles, h) << endl;
}