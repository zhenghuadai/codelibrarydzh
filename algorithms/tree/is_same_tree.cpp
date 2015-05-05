/*
 * =====================================================================================
 *
 *       Filename:  is_same_tree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 03:50:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "common.h"
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if((p == NULL && q != NULL ) || ((p !=NULL) &&(q == NULL))) return false;
        stack<TreeNode*> S0;
        stack<TreeNode*> S1;
        S0.push(p);
        S1.push(q);
        bool isSame = true;
        while(!S0.empty()){
            TreeNode* pTop = S0.top();
            TreeNode* qTop = S1.top();
            S0.pop();
            S1.pop();
            if(pTop == NULL && qTop == NULL) continue;
            if(pTop != NULL && qTop != NULL){
                if(pTop->val != qTop->val){
                    isSame = false;
                    break;
                }
            S0.push(pTop->right);
            S0.push(pTop->left);
            
            
            S1.push(qTop->right);
            S1.push(qTop->left);
            }else{
                isSame = false;
                break;
            } 
        }
        if(S0.size()!= 0 || S1.size() != 0) {
            isSame = false;
        }
        return isSame;
    }
};
