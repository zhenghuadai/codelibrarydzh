/*
 * =====================================================================================
 *
 *       Filename:  islands_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2015 02:59:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "common.h"
#include "utils.h"


int test_numIslands(vector<vector<char>>& grid) ;
static void test1()
{
    vector<vector<char>> T = { {1, 1}};
    vector<vector<char>> T3 = { {1, 1, 0, 0, 0} , {1, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}};
    int num = test_numIslands(T3);
}

static void test()
{
    doTests("graph/islands.testcases", [](json& testcase)->bool{
        vector<vector<char>> a = testcase["data"];
        int result = testcase["result"];
        int r = test_numIslands(a);
        return (result == r);
        });
}

APPEND_TO_TEST(); 
