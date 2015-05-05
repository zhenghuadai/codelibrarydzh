#include "common.h"
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> R;
        TreeNode* p = root;
        stack<TreeNode*> S;
        while(p != NULL || !S.empty()){
            if(p != NULL){
                S.push(p);
                p = p->left;
            }else{
                p = S.top();
                S.pop();
                R.push_back(p->val);
                p = p->right;
            }
        }
        return R;
    }
};
