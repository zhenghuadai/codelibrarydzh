/*
 * =====================================================================================
 *
 *       Filename:  edit_distance.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 06:07:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

/*
 * 0 0 a b c d e 
 * 0 0 1 2 3 4 5 
 * a 1
 * b 2
 * c 3
 * c 4
 * e 5
 */
#include "common.h"
class Solution{
    public:
    int distance(string& s0, string& s1){
        if(s0.size() == 0) return s1.size();
        if(s1.size() == 0) return s0.size();

        int* D = new int[s0.size()];
        for(int i = 0; i < s0.size(); i++){
            D[i] = i+1;
        }

        for(int j = 0; j < s1.size(); j++){
            int pre = j + 1;
            pre = min( j+2, D[0] + 1, j  + ((s0[0] == s1[0])?0:1));
            for(int i = 1; i< s0.size(); i++){
                int R = pre + 1;
                int S = D[i] + 1;
                int T = D[i-1] + ((s0[i] == s1[j])?0:1); 
                D[i-1] = pre;
                pre = min(R, S, T);
            }
            D[s0.size() -1] = pre;
        }
        int d = D[s0.size() -1];
        delete D;
        return d;
    }
    private:
        int min(int R, int S, int T){
            int rs = std::min(R, S);
            return std::min(rs, T);
        }
};

int test_distance(string& s0, string& s1){
    Solution s;
    return s.distance(s0, s1);
}
