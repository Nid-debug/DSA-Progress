// LeetCode 131: Palindrome Partitioning
// Topic: Backtracking | Recursion | String
// Overall Time Complexity: O(2^n * n)
// Overall Space Complexity: O(n) auxiliary (excluding output)

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;   // Stores all valid palindrome partitions
        vector<string> curr;          // Current partition path

        backtrack(s, 0, curr, res);
        return res;
    }

private:
    // Backtracking function to generate all palindrome partitions
    void backtrack(string& s, int start,
                   vector<string>& curr,
                   vector<vector<string>>& res) {

        // Base case: reached end of string
        if (start == s.size()) {
            res.push_back(curr);
            return;
        }

        // Try all possible substrings starting at index 'start'
        for (int end = start; end < s.size(); end++) {

            // Proceed only if substring s[start..end] is palindrome
            if (isPalindrome(s, start, end)) {

                // Choose
                curr.push_back(s.substr(start, end - start + 1));

                // Explore
                backtrack(s, end + 1, curr, res);

                // Un-choose (backtrack)
                curr.pop_back();
            }
        }
    }

    // Helper function to check if a substring is palindrome
    // Time Complexity: O(length of substring)
    bool isPalindrome(string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};
