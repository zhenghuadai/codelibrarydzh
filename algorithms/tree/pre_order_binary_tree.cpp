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
    doTests("tree/pre_order_binary_tree.testcases", [](json& testcase)->bool{
        Solution s;
        string a = testcase["tree"];
        vector<int> result = testcase["result"];
        TreeNode *root;
        istringstream fin(a);
        DM::readBinaryTree(root, fin) ;
        vector<int> r = s.preorderTraversal(root);
        return (result == r);
        });
}
APPEND_TO_TEST(); 
