class Solution {
    int answer;
    // max path going down
    int dfs(TreeNode* root) {
        if(root == NULL) {
            return 0;
        }
        int x = dfs(root->left);
        int y = dfs(root->right);
        answer = max(answer, x + y + root->val);
        return max(0, root->val + max(x, y));
    }
public:
    int maxPathSum(TreeNode* root) {
        answer = INT_MIN;
        dfs(root);
        return answer;
    }
};
