#include "common.h"
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> R;
        stack<TreeNode*> S;
        TreeNode* p = root;
        TreeNode* pre = NULL;
        while(p != NULL || !S.empty()){
            if(p != NULL){
                S.push(p);
                p = p -> left;
            }else {
                TreeNode* q = S.top();
                if(q->right != pre && q->right != NULL){
                   S.push(q->right); 
                   p = q->right->left;
                } else{
                   R.push_back(q->val);
                   pre = S.top();
                   S.pop();
                   p = NULL;
                }
            }
        }
        return R;
    }
};
static void test()
{
}
APPEND_TO_TEST(); 
