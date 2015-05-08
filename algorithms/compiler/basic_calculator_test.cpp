/*
 * =====================================================================================
 *
 *       Filename:  basic_calculator_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 06:37:26 PM
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


int test_calculate(string& s);
static void test()
{
    doTests("compiler/basic_calculator.testcases", [](json& testcase)->bool{
        string a = testcase["expression"];
        int result = testcase["result"];
        int r = test_calculate(a);
        return (result == r);
        });
}
APPEND_TO_TEST(); 
