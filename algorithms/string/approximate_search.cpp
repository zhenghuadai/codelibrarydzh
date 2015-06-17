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

#include "common.h"
class Solution{
    enum{MATCH_SCORE = 0, MISMATCH_SCORE = -1, DELETION_SCORE = -1, INSERTION_SCORE = -1};
    public:
    int approximate_search(string& text, string& pattern){
        if(pattern.size() == 0) return 0;
        if(text.size() == 0) return 0;
        int maxV = -pattern.size();
        int idx = 0;

        int* D = new int[pattern.size()];
        for(int i = 0; i < pattern.size(); i++){
            D[i] = i - pattern.size();
        }

        for(int j = text.size() - 1; j >= 0; j--){
            int pre = 0;
            pre = max( -1, D[pattern.size()-1] -  1, 0  + ((pattern[pattern.size()-1] == text[j])?MATCH_SCORE:MISMATCH_SCORE));
            for(int i = pattern.size()-2; i>=0; i--){
                int R = pre + INSERTION_SCORE;
                int S = D[i] + DELETION_SCORE;
                int T = D[i+1] + ((pattern[i] == text[j])?MATCH_SCORE:MISMATCH_SCORE); 
                D[i+1] = pre;
                pre = max(R, S, T);
            }
            D[0] = pre;
            if(maxV <= pre) { maxV = pre; idx = j;}
        }
        delete D;
        return idx;
    }
 
/*
 * 0 0  a  b  c  d  e 
 * 0 0 -1 -2 -3 -4 -5 
 * a 0
 * b 0
 * c 0
 * c 0
 * e 0
 */
    int approximate_search_returnendpostion(string& text, string& pattern){
        if(pattern.size() == 0) return 0;
        if(text.size() == 0) return 0;
        int maxV = 0;
        int idx = 0;

        int* D = new int[pattern.size()];
        for(int i = 0; i < pattern.size(); i++){
            D[i] = -i - 1;
        }

        for(int j = 0; j < text.size(); j++){
            int pre = 0;
            pre = max( -1, D[0] -  1, 0  + ((pattern[0] == text[0])?0:-1));
            for(int i = 1; i< pattern.size(); i++){
                int R = pre - 1;
                int S = D[i] - 1;
                int T = D[i-1] + ((pattern[i] == text[j])?0:-1); 
                D[i-1] = pre;
                pre = max(R, S, T);
            }
            D[pattern.size() -1] = pre;
            if(maxV < pre) { maxV = pre; idx = j;}
        }
        delete D;
        return idx;
    }
    private:
        int max(int R, int S, int T){
            int rs = std::max(R, S);
            return std::max(rs, T);
        }
};

int test_approximate_search(string& text, string& pattern){
    Solution s;
    return s.approximate_search(text, pattern);
}
