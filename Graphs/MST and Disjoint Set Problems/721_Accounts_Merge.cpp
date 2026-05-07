/*
👥 Problem: Accounts Merge

Given a list of accounts where:
- First element = person's name
- Remaining elements = emails

Two accounts belong to the same person
if they share at least one common email.

Goal:
Merge all accounts belonging to the same person.

Return:
- Name first
- All unique emails sorted lexicographically

-----------------------------------------------------

💡 Approach:

👉 Use Disjoint Set Union (DSU / Union Find)

- Treat each account index as a node
- If two accounts share an email:
    → connect them using union

-----------------------------------------------------

🧠 Step 1: Initialize DSU

- Every account starts as its own parent
- rank[] used for union by rank optimization

-----------------------------------------------------

🧠 Step 2: Map Emails

Use:
unordered_map<string, int>

email → first account index

If email already exists:
- Both accounts belong to same person
- Union them

-----------------------------------------------------

🧠 Step 3: Group Emails By Root Parent

For every email:
- Find its ultimate parent/root
- Put email into that group's list

-----------------------------------------------------

🧠 Step 4: Build Final Answer

For every root:
- Sort emails
- Add account name
- Add all emails

-----------------------------------------------------

⚠️ Key Insight:

Emails are the actual identifiers,
NOT the names.

Two different accounts with same email
must belong to same person.

-----------------------------------------------------

⏱ Time Complexity:

- Traversing emails: O(E)

- DSU operations: Almost O(1)

- Sorting emails: O(E log E)

Final TC: O(E log E)

Where: E = total emails

-----------------------------------------------------

📦 Space Complexity:

- parent array
- rank array
- hash maps

Final SC: O(E + N)

Where: N = number of accounts
*/

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int find(int node, vector<int>& parent) {
        if(parent[node] != node)
            parent[node] = find(parent[node], parent);
        return parent[node];
    }

    void unionNodes(int u, int v, vector<int>& parent, vector<int>& rank) {
        int pu = find(u, parent);
        int pv = find(v, parent);
        if(pu == pv) return;
        if(rank[pu] < rank[pv]) parent[pu] = pv;
        else if(rank[pu] > rank[pv]) parent[pv] = pu;
        else { 
            parent[pv] = pu; rank[pu]++; 
        }
    }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        vector<int> parent(n), rank(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;

        // step 1: map each email to the first account index that owns it
        unordered_map<string, int> emailToAccount;
        for(int i = 0; i < n; i++) {
            for(int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if(emailToAccount.find(email) == emailToAccount.end())
                    emailToAccount[email] = i; // first time seeing this email
                else
                    unionNodes(i, emailToAccount[email], parent, rank); // same email → union
            }
        }

        // step 2: group emails by root account index
        unordered_map<int, vector<string>> rootToEmails;
        for(auto& [email, accountIdx] : emailToAccount) {
            int root = find(accountIdx, parent);
            rootToEmails[root].push_back(email);
        }

        // step 3: build result
        vector<vector<string>> result;
        for(auto& [root, emails] : rootToEmails) {
            sort(emails.begin(), emails.end()); // sort emails
            vector<string> account;
            account.push_back(accounts[root][0]); // add name
            for(auto& email : emails)
                account.push_back(email);
            result.push_back(account);
        }
        return result;
    }
};