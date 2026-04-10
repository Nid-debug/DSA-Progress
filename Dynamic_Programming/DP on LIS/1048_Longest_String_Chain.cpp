#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        // Sort words by length (shortest first)
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });

        // dp[word] = longest chain ending at this word
        unordered_map<string, int> dp;
        int result = 1;

        for (const string& word : words) {
            dp[word] = 1; // Every word is a chain of length 1 by itself

            // Try removing each character one at a time
            for (int i = 0; i < (int)word.size(); i++) {
                string predecessor = word.substr(0, i) + word.substr(i + 1);

                if (dp.count(predecessor)) {
                    dp[word] = max(dp[word], dp[predecessor] + 1);
                }
            }
            result = max(result, dp[word]);
        }
        return result;
    }
};