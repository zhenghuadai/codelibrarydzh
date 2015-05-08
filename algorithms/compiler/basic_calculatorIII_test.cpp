/*
 * =====================================================================================
 *
 *       Filename:  basic_calculatorII_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 06:45:48 PM
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


int test_calculateIII(string& s);
static void test()
{
    doTests("compiler/basic_calculatorIII.testcases", [](json& testcase)->bool{
        string a = testcase["expression"];
        int result = testcase["result"];
        int r = test_calculateIII(a);
        return (result == r);
        });
}
APPEND_TO_TEST(); 
