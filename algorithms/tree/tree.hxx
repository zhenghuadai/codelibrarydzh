/*
 * =====================================================================================
 *
 *       Filename:  tree.hxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 12:26:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "common.h"

template<typename T>
void  preorderTraversal(T* root, function<void(T*)> visit) {
    if(root == NULL) return ;
    stack<TreeNode*> S;
    S.push(root);
    while(!S.empty()){
        TreeNode* p = S.top();
        visit(p);
        S.pop();
        if(p->right != NULL) S.push(p->right);
        if(p->left != NULL) S.push(p->left);
    }
}

template<typename T>
void inorderTraversal(T* root, function<void(T*)> visit) {
    T* p = root;
    stack<T*> S;
    while(p != nullptr || !S.empty()){
        if(p != nullptr ){
            S.push(p);
            p = p->left;
        }else{
            p = S.top();
            S.pop();
            visit(p);
            p = p->right;
        }
    }
}

template<typename T>
void postorderTraversal(T* root, function<void(T*)> visit) {
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
                visit(q);
                pre = S.top();
                S.pop();
                p = NULL;
            }
        }
    }
}
