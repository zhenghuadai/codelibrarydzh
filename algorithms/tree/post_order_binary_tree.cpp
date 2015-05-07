#include "common.h"
#include "tree.hxx"


class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> R;
        ::postorderTraversal<TreeNode>(root, [&R](TreeNode* p){
                R.push_back(p->val);
                });
        return R;
    }
    vector<int> postorderTraversal1(TreeNode* root) {
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

vector<int> test_postorderTraversal(TreeNode* root) {
    Solution s;
    return s.postorderTraversal(root);
}
