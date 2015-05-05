#include "common.h"
class Solution {
public:

    bool balanced;
    int D(TreeNode * root)
    {
        int l = 0;
        int r = 0;
        if(root->left) l = D(root->left);
        if(root->right) r = D(root->right);
        if( abs(l - r) > 1) balanced = false;
        return max(l, r)+1;
    }
    
    bool isBalanced(TreeNode* root) {
        if(root == NULL) return true;
        balanced = true;
        D(root);
        return balanced;
    }
};
