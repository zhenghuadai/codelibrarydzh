/*
 * =====================================================================================
 *
 *       Filename:  arrary_to_binary_tree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 03:15:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "common.h"
namespace{
class Solution {
public:

    void S(TreeNode* root, vector<int>& nums, int start, int end)
    {
        int mid = (end  + start) /2;
        if(( ( end - start + 1) & 1 ) == 1) {
            
        }
        if(end - start == 0){
            root -> val = nums[start];
            return;
        }else if(end -start == 1){
            root-> val = nums[start];
            root->right = new TreeNode(nums[end]);
        }else{
            root -> val = nums[mid];
            root -> left = new TreeNode(0);
            root -> right = new TreeNode(0);
            S(root->left, nums, start, mid -1);
            S(root->right, nums, mid+1, end);
        }
        
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.size() == 0) return NULL;
        TreeNode * root= new TreeNode(0);
        S(root, nums, 0, nums.size()-1);
        return root;
    }
};
} ///namespace

TreeNode* test_sortedArrayToBST(vector<int>& nums) {
    Solution s;
    return s.sortedArrayToBST(nums);
}
