// ------------------------
// Delete Node using Inorder Successor
// ------------------------
class SolutionSuccessor {
public:
    // Find inorder successor (smallest in right subtree)
    TreeNode* getInorderSuccessor(TreeNode* root) {
        while (root && root->left)
            root = root->left;
        return root;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        if (key < root->val)
            root->left = deleteNode(root->left, key);
        else if (key > root->val)
            root->right = deleteNode(root->right, key);
        else {
            // Node with one or zero child
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children: replace with inorder successor
            TreeNode* successor = getInorderSuccessor(root->right);
            root->val = successor->val;
            root->right = deleteNode(root->right, successor->val);
        }
        return root;
    }
};

// ------------------------
// Delete Node using Inorder Predecessor
// ------------------------
class SolutionPredecessor {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        if (key < root->val)
            root->left = deleteNode(root->left, key);
        else if (key > root->val)
            root->right = deleteNode(root->right, key);
        else {
            // Node with one or zero child
            if (!root->left) return root->right;
            if (!root->right) return root->left;

            // Node with two children: replace with inorder predecessor
            TreeNode* temp = root->left;
            while (temp->right)
                temp = temp->right;
            root->val = temp->val;
            root->left = deleteNode(root->left, temp->val);
        }
        return root;
    }
};