#include "common.h"
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> R;
        if(root == NULL) return R;
        stack<TreeNode*> S;
        S.push(root);
        while(!S.empty()){
            TreeNode* p = S.top();
            R.push_back(p->val);
            S.pop();
            if(p->right != NULL) S.push(p->right);
            if(p->left != NULL) S.push(p->left);
        }
        return R;
    }
};
static void test()
{
}
APPEND_TO_TEST(); 
