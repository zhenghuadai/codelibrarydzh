/*
 * =====================================================================================
 *
 *       Filename:  median_two_sort_array.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 03:59:01 AM
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

    int getKthFromTwoSortedArray(vector<int>& nums1, vector<int>& nums2, int k, int& valueK, int& valueK1){
        int m = nums1.size();
        int n = nums2.size();
        int leftM = 0, rightM = m;
        int leftN = 0, rightN = n;
        while(leftM < rightM && leftN < rightN && k >=2){
            int middleM = std::min(rightM - leftM, k / 2);
            int middleN = std::min(rightN - leftN, k / 2);
            if(nums1[leftM + middleM -1] > nums2[leftN + middleN -1]){
                leftN += middleN;
                k -= middleN;
            }else{
                leftM += middleM;
                k -= middleM;
            }
        }
        
        if(leftM == rightM){
            valueK = nums2[leftN + k -1];
            valueK1 = nums2[leftN + k ];
        }else if(leftN == rightN){
            valueK = nums1[leftM + k -1];
            valueK1 = nums1[leftM + k];
        }else if(k == 1){
            //valueK = std::min(nums1[leftM], nums2[leftN]);
            if( nums1[leftM] < nums2[leftN]){
                valueK =  nums1[leftM];
                valueK1 = nums2[leftN];
            }else{
                valueK = nums2[leftN];
                valueK1 =  nums1[leftM];
            }
            
            if(leftN + 1< rightN ){
                valueK1 = std::min(valueK1, nums2[leftN + 1]);
            }
            
            if(leftM + 1 < rightM){
                valueK1 = std::min(valueK1, nums1[leftM + 1]);
            }
            
        }else if(k == 0){
            return -1;
        }
        return 0;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int s = nums1.size() + nums2.size();
        int numK, numK1;
        if(s%2 == 1) {
            getKthFromTwoSortedArray(nums1, nums2, s/2+1, numK, numK1);
            return numK;
        }else{
            getKthFromTwoSortedArray(nums1, nums2, s/2, numK, numK1);
            return ((double)(numK + numK1))/2.0;
        }
    }
};
