/*
 * =====================================================================================
 *
 *       Filename:  isIsomorphic_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 01:57:24 AM
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

bool test_isIsomorphic(string s, string t) ;
static void test()
{
    doTests("string/isIsomorphic.testcases", [](json& testcase)->bool{
            string a = testcase["text1"];
            string b = testcase["text2"];
            //        bool result = testcase["result"].get<int>() == 0? false:true;
            bool result = testcase["result"];
            bool r = test_isIsomorphic(a,b);
            return (result == r);
            });
}
APPEND_TO_TEST(); 
