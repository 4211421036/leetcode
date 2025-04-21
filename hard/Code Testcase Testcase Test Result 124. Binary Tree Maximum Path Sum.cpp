/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int max_sum = INT_MIN;
        maxPathSumHelper(root, max_sum);
        return max_sum;
    }
    
private:
    int maxPathSumHelper(TreeNode* node, int& max_sum) {
        if (!node) return 0;
        
        int left_max = max(maxPathSumHelper(node->left, max_sum), 0);
        int right_max = max(maxPathSumHelper(node->right, max_sum), 0);
        
        int current_sum = node->val + left_max + right_max;
        max_sum = max(max_sum, current_sum);
        
        return node->val + max(left_max, right_max);
    }
};
