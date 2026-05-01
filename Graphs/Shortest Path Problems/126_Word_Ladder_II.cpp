/*
🪜 Problem: Word Ladder II

Given beginWord, endWord and a wordList,
return ALL shortest transformation sequences from beginWord → endWord.

Rules:
- Only one character can change at a time
- Each intermediate word must exist in wordList
- Return all shortest paths

-----------------------------------------------------

💡 Approach:
1. This is BFS (shortest path), but we need ALL paths.
2. Store entire path in queue instead of just word.
3. Use level-based BFS:
   - Track words used in current level (levelVisited)
   - Remove them AFTER level finishes
   → ensures shortest paths only
4. Once we reach endWord:
   - mark found = true
   - collect paths but DO NOT go deeper levels

-----------------------------------------------------

⚠️ Key Trick:
- Don't erase words immediately → only after level ends
- Otherwise you'll lose valid shortest paths

-----------------------------------------------------

⏱ Time Complexity:
- In worst case, exponential due to storing paths
- Roughly: O(N * L * 26 + number_of_paths)

📦 Space Complexity:
- Queue stores full paths → O(N * path_length)
- Set: O(N)
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        vector<vector<string>> result;

        if(wordSet.find(endWord) == wordSet.end()) return result;

        // BFS — store entire path in queue
        queue<vector<string>> q;
        q.push({beginWord});
        wordSet.erase(beginWord);

        bool found = false;

        while(!q.empty() && !found) {
            int size = q.size();
            unordered_set<string> levelVisited; // words visited in THIS level

            for(int i = 0; i < size; i++) {
                vector<string> path = q.front(); q.pop();
                string word = path.back();

                for(int j = 0; j < word.size(); j++) {
                    string newWord = word;
                    for(char c = 'a'; c <= 'z'; c++) {
                        if(c == word[j]) continue;
                        newWord[j] = c;

                        if(wordSet.find(newWord) != wordSet.end()) {
                            vector<string> newPath = path;
                            newPath.push_back(newWord);

                            if(newWord == endWord) {
                                result.push_back(newPath);
                                found = true;
                            } else {
                                q.push(newPath);
                            }
                            levelVisited.insert(newWord);
                        }
                    }
                }
            }
            // erase all words used in this level so next level can't reuse them
            for(auto& w : levelVisited) wordSet.erase(w);
        }
        return result;
    }
};