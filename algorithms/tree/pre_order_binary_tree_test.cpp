/*
 * =====================================================================================
 *
 *       Filename:  pre_order_binary_tree_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 02:04:54 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "common.h"
#include "utils.h"


vector<int> test_preorderTraversal(TreeNode* root) ;
static void test()
{
    doTests("tree/pre_order_binary_tree.testcases", [](json& testcase)->bool{
        string a = testcase["tree"];
        vector<int> result = testcase["result"];
        TreeNode *root;
        istringstream fin(a);
        DM::readBinaryTree(root, fin) ;
        vector<int> r = test_preorderTraversal(root);
        return (result == r);
        });
}
APPEND_TO_TEST(); 
