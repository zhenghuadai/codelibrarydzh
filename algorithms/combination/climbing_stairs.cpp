#include "common.h"
class Solution {
public:
   int climbStairs1(int n) {
        if(n == 1) return 1;
        if(n == 2) return 2;
        int NN = 0;
        int n1 = 1, n2 = 2;
        for(int i = 3; i<=n; i++){
            NN = n1 + n2;
            n1 = n2;
            n2 = NN;
        }
        return NN;
    }
public:
   /******************************
    *假设上一步2的个数为a，1的个数为b。
    *那么这一步2的个数为a+1, 1的个数为b-2。
    *上一步（a个2步，b个1步）所有的走法数为 (a+b)!/(a!b!)
    *这一步的所有走法数为 (a+b-1)!/((a+1)!(b-2)!) == ( (a+b)!/(a!b!) ) * (b*(b-1)/((a+b)*(a+1))) 
    ******************************/
   int climbStairs(int n) {
       if(n <= 3) return n;
       int maxTwos = n /2;
       int result = 1;
       int start = n -1;
       result += n-1;
       for(int i=2; i<= maxTwos; i++){
           long long  lastTwos = i-1;
           long long lastOnes = n - (2* (i-1));
           int cur = start * (lastOnes * (lastOnes-1))/((lastTwos + lastOnes)*(lastTwos +1));
           result += cur;
           start = cur;
           printf("i:%d (%d %d) : %d   == %d\n", i, (int)lastTwos, (int)lastOnes, (int)cur, result);
       }
       return result;
   }
};
