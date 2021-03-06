#include "common.h"
#include "tree.hxx"

namespace{
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> R;
        if(root == NULL) return R;
        ::preorderTraversal<TreeNode>(root, [&R](TreeNode* p){
                R.push_back(p->val);
                });

    }
    vector<int> preorderTraversal1(TreeNode* root) {
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
}/// namespace

vector<int> test_preorderTraversal(TreeNode* root) {
    Solution s;
    return std::move(s.preorderTraversal(root));
}
