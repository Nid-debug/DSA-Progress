class Solution {	
public:
    vector<int> floorCeilOfBST(TreeNode* root, int key) {
        int floorVal = -1, ceilVal = -1;
        TreeNode* curr = root;
        
        while (curr) {
            if (curr->data == key) {
                floorVal = ceilVal = curr->data;
                break;
            } 
            else if (curr->data < key) {
                floorVal = curr->data;
                curr = curr->right;
            } 
            else {
                ceilVal = curr->data;
                curr = curr->left;
            }
        }
        return {floorVal, ceilVal};
    }
};