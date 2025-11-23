class Solution {
public:
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;  
        }
    };
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;
        
        for (ListNode* list : lists) {
            if (list != nullptr) {  
                minHeap.push(list);
            }
        }
        
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        
        while (!minHeap.empty()) {
            ListNode* minNode = minHeap.top();
            minHeap.pop();
            
            current->next = minNode;
            current = current->next;
            
            if (minNode->next != nullptr) {
                minHeap.push(minNode->next);
            }
        }
        return dummy->next;
    }
};