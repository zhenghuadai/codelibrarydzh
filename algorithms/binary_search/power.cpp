/*
 * =====================================================================================
 *
 *       Filename:  power.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 03:55:14 AM
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
    double myPow(double x, int n){
       if (n == 0) return 1;  
       double result = 1;
        bool s = (n < 0);
        if (n < 0) n = -n;
        while (n > 0)  
        {  
            if ((n & 1) != 0)  
                result *= x;  
            x *= x;  
            n >>= 1;  
        }  
        return s?(1/result):result;  
    }
    double myPow1(double x, int n) {
       double y = 1.0;
       bool t=n>0;
       if(n==0)return 1.0;
       if(n<0)n=-n;
       for(;n > 0;n>>=1){
         if(n&1){
           y*=x;
         }
       //if(n<2)break;
         x*=x;
        
        }
        return t?y:1/y;}
};
