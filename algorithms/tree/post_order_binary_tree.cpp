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
    doTests("tree/post_order_binary_tree.testcases", [](json& testcase)->bool{
        Solution s;
        string a = testcase["tree"];
        vector<int> result = testcase["result"];
        TreeNode *root;
        istringstream fin(a);
        DM::readBinaryTree(root, fin) ;
        vector<int> r = s.postorderTraversal(root);
        return (result == r);
        });

}
APPEND_TO_TEST(); 
