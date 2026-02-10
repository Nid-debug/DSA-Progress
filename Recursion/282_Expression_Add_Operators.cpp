#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        if (num.empty()) return result;
        backtrack(result, num, target, "", 0, 0, 0);
        return result;
    }

private:
    void backtrack(vector<string>& res, const string& num, int target, string path, int index, long currentVal, long prevVal) {
        // Base case: reached the end of the string
        if (index == num.length()) {
            if (currentVal == target) {
                res.push_back(path);
            }
            return;
        }

        for (int i = index; i < num.length(); ++i) {
            // Handle leading zeros: "05" is invalid, but "0" is fine
            if (i > index && num[index] == '0') break;

            string part = num.substr(index, i - index + 1);
            long val = stol(part);

            if (index == 0) {
                // First number: no operator needed
                backtrack(res, num, target, part, i + 1, val, val);
            } else {
                // Try Addition
                backtrack(res, num, target, path + "+" + part, i + 1, currentVal + val, val);

                // Try Subtraction
                backtrack(res, num, target, path + "-" + part, i + 1, currentVal - val, -val);

                // Try Multiplication
                // To maintain precedence: undo the previous operation and multiply
                backtrack(res, num, target, path + "*" + part, i + 1, currentVal - prevVal + (prevVal * val), prevVal * val);
            }
        }
    }
};