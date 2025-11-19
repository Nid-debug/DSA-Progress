#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>
using namespace std;

class Solution {
public:
    // Solution 1: Min Heap - O(n log k)
    vector<int> topKFrequentHeap(vector<int>& nums, int k) {
        // Step 1: Count frequency of each element
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }
        
        // Step 2: Use min heap to keep top k frequent elements
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        for (auto &p : freqMap) {
            int num = p.first;
            int freq = p.second;
            minHeap.push({freq, num});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // Step 3: Extract result
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
    
    // Solution 2: Bucket Sort - O(n) MOST OPTIMAL!
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Step 1: Count frequency of each element
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }
        
        // Step 2: Create buckets where index = frequency
        // bucket[i] contains all elements with frequency i
        vector<vector<int>> bucket(n + 1);
        for (auto &p : freqMap) {
            int num = p.first;
            int freq = p.second;
            bucket[freq].push_back(num);
        }
        
        // Step 3: Collect top k elements from highest frequency to lowest
        vector<int> result;
        for (int i = n; i >= 0 && result.size() < k; i--) {
            for (int num : bucket[i]) {
                result.push_back(num);
                if (result.size() == k) {
                    break;
                }
            }
        }
        return result;
    }
};