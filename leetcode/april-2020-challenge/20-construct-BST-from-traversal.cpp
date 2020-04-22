/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode* helper(const vector<int>& preorder, int& id, int limit) {
        if(id == (int) preorder.size() || preorder[id] > limit) {
            return NULL;
        }
        int root_value = preorder[id];
        TreeNode* root = new TreeNode(root_value);
        id++;
        root->left = helper(preorder, id, root_value);
        root->right = helper(preorder, id, limit);
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int id = 0;
        return helper(preorder, id, INT_MAX);
        /*
        // O(N) space and time
        if(preorder.empty()) {
            return NULL;
        }
        int root_value = preorder[0];
        TreeNode* root = new TreeNode(root_value);
        root->left = bstFromPreorder(preorder)
        vector<int> smaller, greater;
        for(int i = 1; i < (int) preorder.size(); ++i) {
            if(preorder[i] < root_value) {
                smaller.push_back(preorder[i]);
            }
            else {
                greater.push_back(preorder[i]);
            }
        }
        cerr << root_value << " " << smaller.size() << " " << greater.size() << endl;
        root->left = bstFromPreorder(smaller);
        root->right = bstFromPreorder(greater);
        return root;*/
    }
};
