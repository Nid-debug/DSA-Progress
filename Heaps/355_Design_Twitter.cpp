#include <bits/stdc++.h>
using namespace std;

class Twitter {
private:
    unordered_map<int, vector<pair<int, int>>> tweets;
    
    unordered_map<int, unordered_set<int>> following;

    int timestamp;
    
public:
    Twitter() {
        timestamp = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timestamp++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        priority_queue<pair<int, int>> maxHeap;
        
        if (tweets.find(userId) != tweets.end()) {
            for (auto& tweet : tweets[userId]) {
                maxHeap.push(tweet);
            }
        }
        
        if (following.find(userId) != following.end()) {
            for (int followeeId : following[userId]) {
                if (tweets.find(followeeId) != tweets.end()) {
                    for (auto& tweet : tweets[followeeId]) {
                        maxHeap.push(tweet);
                    }
                }
            }
        }
        
        vector<int> newsFeed;
        int count = 0;
        while (!maxHeap.empty() && count < 10) {
            newsFeed.push_back(maxHeap.top().second); // second is tweetId
            maxHeap.pop();
            count++;
        }
        
        return newsFeed;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            following[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        if (following.find(followerId) != following.end()) {
            following[followerId].erase(followeeId);
        }
    }
};