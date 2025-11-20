#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Twitter {
private:
    // Store tweets: userId -> vector of (timestamp, tweetId)
    unordered_map<int, vector<pair<int, int>>> tweets;
    
    // Store following relationships: userId -> set of userIds they follow
    unordered_map<int, unordered_set<int>> following;
    
    // Global timestamp to track tweet order
    int timestamp;
    
public:
    Twitter() {
        timestamp = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        // Add tweet with current timestamp
        tweets[userId].push_back({timestamp++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        // Max heap to store (timestamp, tweetId)
        // Priority queue is max heap by default
        priority_queue<pair<int, int>> maxHeap;
        
        // Add user's own tweets to heap
        if (tweets.find(userId) != tweets.end()) {
            for (auto& tweet : tweets[userId]) {
                maxHeap.push(tweet);
            }
        }
        
        // Add tweets from all users that userId follows
        if (following.find(userId) != following.end()) {
            for (int followeeId : following[userId]) {
                if (tweets.find(followeeId) != tweets.end()) {
                    for (auto& tweet : tweets[followeeId]) {
                        maxHeap.push(tweet);
                    }
                }
            }
        }
        
        // Get top 10 most recent tweets
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
        // User cannot follow themselves
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