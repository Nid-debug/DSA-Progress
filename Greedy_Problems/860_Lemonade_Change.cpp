#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;

        for (int b : bills) {
            if (b == 5) {
                five++;
            }
            else if (b == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            }
            else { // b == 20
                // Prefer giving 10 + 5 (best greedy choice)
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                }
                // Otherwise give three 5s
                else if (five >= 3) {
                    five -= 3;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution sol;
    vector<int> bills = {5, 5, 5, 10, 20};

    cout << sol.lemonadeChange(bills) << endl;  //Expected Output = 1
    return 0;
}