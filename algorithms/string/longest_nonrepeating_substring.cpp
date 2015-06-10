/*
 * =====================================================================================
 *
 *       Filename:  longest_nonrepeating_substring.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/09/2015 11:32:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "common.h"

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int lastIndex[256] = {-1};
        int maxDistance = -1;
        int lastDistance = 0;
        for(int i = 0;i<256;i++)lastIndex[i] = -1;
        for(int i = 0; i< s.size(); i ++){
            int distance = i - lastIndex[s[i]];
            if(distance > lastDistance + 1){
                lastDistance = lastDistance + 1;
            }else{
                lastDistance = distance -1;
            }
            if(maxDistance < lastDistance) maxDistance = lastDistance;
            lastIndex[s[i]] = i;
        }
        return (maxDistance + 1);
    }
};

static void test()
{
    doTests("string/longest_nonrepeating_substring.testcases", [](json& testcase)->bool{
        Solution s;
        string a = testcase["text"];
        int result = testcase["result"];
        int r = s.lengthOfLongestSubstring(a);
        return (result == r);
        });

}
APPEND_TO_TEST(); 
