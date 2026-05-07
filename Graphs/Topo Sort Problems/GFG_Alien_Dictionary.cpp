/*
🔤 Problem: Alien Dictionary

Given a sorted dictionary of an alien language,
find the order of characters in that language.

Example:
words = ["baa", "abcd", "abca", "cab", "cad"]

Possible order:
"bdac"

-----------------------------------------------------

💡 Approach:

👉 Key Idea:
- Compare adjacent words
- First different character gives ordering

Example:
"abcd"
"abca"

First different chars:
'd' comes before 'a'

So:
d → a

This becomes a directed graph problem.

-----------------------------------------------------

🧠 Steps:

1. Collect all unique characters

2. Build graph:
   - Compare adjacent words
   - Find first mismatching character
   - Create directed edge:
       char1 → char2

3. Perform Topological Sort (Kahn's Algorithm)

4. Convert topo order back into string

-----------------------------------------------------

⚠️ Important Edge Case:

If:
"abc"
comes before
"ab"

This is invalid because longer prefix cannot come first.

Return "".

-----------------------------------------------------

⏱ Time Complexity:
- Building graph: O(N * L)
- Topo Sort: O(V + E)

Overall:
O(N * L + V + E)

Where:
- N = number of words
- L = average word length
- V = unique characters
- E = edges between characters

-----------------------------------------------------

📦 Space Complexity:
- Graph + indegree + mappings: O(V + E)
*/

#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution{
public:
    vector<int> topoSort(int V, vector<int> adj[]){
        vector<int> indegree(V, 0);
        
        for(int i = 0; i < V; i++) {
            for(auto it : adj[i]) {
                indegree[it]++;
            }
        }
        
        queue<int> q;
        for(int i = 0; i < V; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            } 
        }
        vector<int> topo;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            for(auto it : adj[node]) {
                indegree[it]--;
                if(indegree[it] == 0) q.push(it);
            }
        }
        return topo;
    }
    
public:
    string findOrder(vector<string> &words) {
        // step 1: collect all unique chars and map them to integers
        unordered_map<char, int> charToInt;
        int n = words.size();
        int id = 0;
        for(auto& word : words)
            for(char c : word)
                if(charToInt.find(c) == charToInt.end())
                    charToInt[c] = id++;

        int V = id;
        vector<int> adj[V];

        // step 2: build graph
        for(int i = 0; i < n - 1; i++) {
            string s1 = words[i];
            string s2 = words[i + 1];
            int len = min(s1.size(), s2.size());
            bool found = false;

            for(int ptr = 0; ptr < len; ptr++) {
                if(s1[ptr] != s2[ptr]) {
                    adj[charToInt[s1[ptr]]].push_back(charToInt[s2[ptr]]);
                    found = true;
                    break;
                }
            }
            // edge case: "abc" before "ab" is invalid
            if(!found && s1.size() > s2.size()) return "";
        }

        // step 3: run topoSort
        vector<int> topo = topoSort(V, adj);

        // cycle check
        if(topo.size() != V) return "";

        // step 4: convert back int to char
        unordered_map<int, char> intToChar;
        for(auto& [c, i] : charToInt)
            intToChar[i] = c;

        string ans = "";
        for(auto it : topo)
            ans += intToChar[it];

        return ans;
    }
};