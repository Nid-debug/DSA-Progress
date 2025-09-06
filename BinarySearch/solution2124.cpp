#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkString(string s) {
        for (int i = 1; i < s.size(); i++) {
            if (s[i-1] == 'b' && s[i] == 'a') {
                return false; 
            }
        }
        return true;
    }
};

int main() {
    Solution p;
    string s = "aabbb";
    cout << p.checkString(s) << endl;
}