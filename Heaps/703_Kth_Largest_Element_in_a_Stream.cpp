#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: Constructor O(n log k) Process n initial elements
//                  add() O(log k) Heap insert/delete
// Space Complexity: O(k) Store only k largest elements

class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min heap
    int k;
    
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        
        // Add all initial numbers to the heap
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        // Add the new value to heap
        minHeap.push(val);
        
        // If heap size exceeds k, remove the smallest element
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        
        // The top of the heap is the kth largest element
        return minHeap.top();
    }
};

int main() {
    // Test case: ["KthLargest", "add", "add", "add", "add", "add"]
    //            [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
    
    int k = 3;
    vector<int> nums = {4, 5, 8, 2};
    
    KthLargest* obj = new KthLargest(k, nums);
    
    cout << "Constructor initialized with k=" << k << " and nums=[4, 5, 8, 2]" << endl;
    cout << "----------------------------------------------------" << endl;
    
    cout << "add(3) returns: " << obj->add(3) << endl;
    cout << "add(5) returns: " << obj->add(5) << endl;
    cout << "add(10) returns: " << obj->add(10) << endl;
    cout << "add(9) returns: " << obj->add(9) << endl;
    cout << "add(4) returns: " << obj->add(4) << endl;
    
    cout << "----------------------------------------------------" << endl;
    cout << "Expected output: [null, 4, 5, 5, 8, 8]" << endl;
    
    delete obj;
    
    return 0;
}