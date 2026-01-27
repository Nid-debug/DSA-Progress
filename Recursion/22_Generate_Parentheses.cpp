class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        solve(0, 0, "", n, result);
        return result;        
    }

    void solve(int openP, int closeP, string s, int n, vector<string>& result) {
        if (openP == n && closeP == n) {
            result.push_back(s);
            return;
        }

        if (openP < n) {
            solve(openP + 1, closeP, s + "(", n, result);
        }

        if (closeP < openP) {
            solve(openP, closeP + 1, s + ")", n, result);
        }
    }
};

