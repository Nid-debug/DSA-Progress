#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> result;
        string current = "";
        backtrack(digits, 0, current, result);
        return result;
    }
    
private:
    const vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
    void backtrack(string& digits, int index, string& current, vector<string>& result) {
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }
        
        int digit = digits[index] - '0';
        string letters = phone[digit];
        
        for (char c : letters) {
            current.push_back(c);
            backtrack(digits, index + 1, current, result);
            current.pop_back();
        }
    }
};

int main() {
    Solution sol;
    string digits = "23";
    
    vector<string> final = sol.letterCombinations(digits);

    for(const string& combination : final) {
       cout << combination << endl;
    }
    
    return 0;
}