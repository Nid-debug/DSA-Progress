#include <iostream>
using namespace std;

class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;   // minimum possible '(' count
        int high = 0;  // maximum possible '(' count

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                if (low > 0) low--;
                high--;
            }
            else { // '*'
                // '*' can act as '(', ')' or empty
                if (low > 0) low--;   // treat '*' as ')'
                high++;               // treat '*' as '('
            }

            // If high < 0, too many ')' at some point
            if (high < 0) return false;
        }

        // low == 0 means we can balance all '('
        return low == 0;
    }
};

int main() {
    Solution sol;
    string s = "(*))";

    cout << sol.checkValidString(s) << endl; //Expected Output : 1
}