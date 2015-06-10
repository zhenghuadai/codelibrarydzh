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
static void test()
{
    doTests("tree/in_order_binary_tree.testcases", [](json& testcase)->bool{
        Solution s;
        string a = testcase["tree"];
        vector<int> result = testcase["result"];
        TreeNode *root;
        istringstream fin(a);
        DM::readBinaryTree(root, fin) ;
        vector<int> r = s.inorderTraversal(root);
        return (result == r);
        });
}
APPEND_TO_TEST(); 
