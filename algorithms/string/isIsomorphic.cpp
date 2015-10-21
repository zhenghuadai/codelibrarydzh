/*
 * =====================================================================================
 *
 *       Filename:  Isomorphic.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2015 10:30:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "common.h"

namespace{
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size()) return false;
        bool ret = true;
        char cmap[128] = {0};
        char used[128] = {0};
        for(int i = 0; i<s.size() ; i++){
            char si = s[i];
            char ti = t[i];
            if(cmap[si] == 0){
                if(used[ti] == 1){
                    ret = false;
                    break;
                }else{
                cmap[si] = ti;
                used[ti] = 1;
                }
            }else if(cmap[si] != ti){
                ret = false;
                break;
            }
        }
        return ret;
    }
};
} /// namespace 

bool test_isIsomorphic(string str, string t) {
    Solution s;
    return s.isIsomorphic(str,t);
}
