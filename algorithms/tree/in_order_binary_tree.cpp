#include "common.h"
#include "tree.hxx"
namespace{ 

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> R;
        ::inorderTraversal<TreeNode>(root, [&R](TreeNode* p){
                R.push_back(p->val);
                });
        return R;
    }

    vector<int> inorderTraversal1(TreeNode* root) {
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
} ///namespace

vector<int> test_inorderTraversal(TreeNode* root) {
    Solution s;
    return s.inorderTraversal(root);
}

