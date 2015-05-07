/*
 * =====================================================================================
 *
 *       Filename:  edit_distance_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 06:08:22 AM
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

int test_distance(string& s0, string& s1);
static void test()
{
    doTests("string/edit_distance.testcases", [](json& testcase)->bool{
            string a = testcase["text1"];
            string b = testcase["text2"];
            int result = testcase["result"];
            int r = test_distance(a,b);
            return (result == r);
            });
}
APPEND_TO_TEST(); 
