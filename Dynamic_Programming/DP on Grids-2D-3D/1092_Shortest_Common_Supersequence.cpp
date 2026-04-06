#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string solve(int i, int j, string& s1, string& s2) {
        // base cases
        if (i == 0) return s2.substr(0, j);  // s1 exhausted, take remaining s2
        if (j == 0) return s1.substr(0, i);  // s2 exhausted, take remaining s1

        if (s1[i-1] == s2[j-1])
            return solve(i-1, j-1, s1, s2) + s1[i-1];

        string left  = solve(i-1, j, s1, s2) + s1[i-1];
        string right = solve(i, j-1, s1, s2) + s2[j-1];

        return left.size() < right.size() ? left : right;
    }

    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size(), n = str2.size();
        return solve(m, n, str1, str2);
    }
};

int main() {
    Solution sol;
    string str1 = "abac";
    string str2 = "cab";
    cout << sol.shortestCommonSupersequence(str1, str2);
}