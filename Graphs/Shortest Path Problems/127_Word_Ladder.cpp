/*
🧩 Problem: Word Ladder

Given two words (beginWord and endWord), and a dictionary (wordList),
return the length of the shortest transformation sequence from beginWord → endWord.

Rules:
- Only one letter can be changed at a time
- Each transformed word must exist in wordList

If no transformation is possible → return 0

-----------------------------------------------------

💡 Approach:
1. This is a shortest path problem → use BFS.
2. Each word is a node, edges exist if:
   - words differ by exactly one character
3. Start BFS from beginWord.
4. For each word:
   - Try changing every character (a → z)
   - If new word exists in set → push to queue
5. Use unordered_set for:
   - O(1) lookup
   - marking visited (by erase)

-----------------------------------------------------

⏱ Time Complexity:
- For each word, we try:
  → L positions
  → 26 characters
=> O(N * L * 26) ≈ O(N * L)

Where:
- N = number of words
- L = length of each word

📦 Space Complexity:
- Set + Queue: O(N)
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // edge case: endWord not in wordList
        if(wordSet.find(endWord) == wordSet.end()) return 0;

        queue<pair<string, int>> q; // {word, steps}
        q.push({beginWord, 1});
        wordSet.erase(beginWord); // mark visited

        while(!q.empty()) {
            auto [word, steps] = q.front(); q.pop();

            // try changing every character at every position
            for(int i = 0; i < word.size(); i++) {
                string newWord = word;
                for(char c = 'a'; c <= 'z'; c++) {
                    if(c == word[i]) continue; // same char, skip
                    newWord[i] = c;

                    if(newWord == endWord) return steps + 1; // found!

                    if(wordSet.find(newWord) != wordSet.end()) {
                        wordSet.erase(newWord); // mark visited
                        q.push({newWord, steps + 1});
                    }
                }
            }
        }
        return 0; // no path found
    }
};