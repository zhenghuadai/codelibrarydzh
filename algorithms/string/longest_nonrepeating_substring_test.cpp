/*
 * =====================================================================================
 *
 *       Filename:  longest_nonrepeating_substring_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 01:59:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "common.h"
#include "utils.h"

int test_lengthOfLongestSubstring(string& s) ;
static void test()
{
    doTests("string/longest_nonrepeating_substring.testcases", [](json& testcase)->bool{
        string a = testcase["text"];
        int result = testcase["result"];
        int r = test_lengthOfLongestSubstring(a);
        return (result == r);
        });

}
APPEND_TO_TEST(); 
