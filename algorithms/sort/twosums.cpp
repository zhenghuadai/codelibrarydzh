/*
 * =====================================================================================
 *
 *       Filename:  twosums.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 04:00:50 AM
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
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        vector<int> nums2 = nums;
        std::sort(nums2.begin(), nums2.end());
        for(int i = 0; i < nums2.size() -1; i++){
            int a = nums2[i];
            int b = target - a;
            vector<int>::iterator iterB;
            iterB = std::lower_bound (nums2.begin() + i + 1, nums2.end(), b);
            if( (nums2.end() != iterB) && (b == *iterB)){
               
                    int index1 = std::find(nums.begin(), nums.end(), a) - nums.begin();
                    int index2;
                    if(a == b){
                        index2 = std::find(nums.begin() + index1 + 1, nums.end(), b) - nums.begin();
                    }else{
                        index2 = std::find(nums.begin(), nums.end(), b) - nums.begin();
                    }
                    if(index1>index2){
                        int tmp = index1;
                        index1 = index2;
                        index2 = tmp;
                    }
                    result.push_back(index1+1);
                    result.push_back(index2+1);
                    break;
               
            }
        }
        return result;
    }
};

vector<int> test_twoSum(vector<int>& nums, int target) { 
    Solution s;
    return s.twoSum(nums, target);
}
