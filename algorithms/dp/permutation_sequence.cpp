/*
 * =====================================================================================
 *
 *       Filename:  permutation_sequence.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 03:54:16 AM
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
    string getPermutation(int n, int k) {
        vector<int> nums;
        for(int i = 1; i<=n; i++) nums.push_back(i);
        string result;
        
        int t = 1;
        for(int i = 1; i< n ; i++)
          t = t*i;
        for(int it = n -1; it > 0; it--){
            int m = (k-1) / t ;
            result.push_back(nums[m] + '0');
            nums.erase(nums.begin() + m);
            k -= (m * t);
            t = t / (it);
        }
        result.push_back(nums[0]+'0');
        return result;
    }
};
