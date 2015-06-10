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

#include "islands.cpp"



static void test1()
{
    vector<vector<char>> T = { {1, 1}};
    vector<vector<char>> T3 = { {1, 1, 0, 0, 0} , {1, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}};
    Solution s;
    int num = s.numIslands(T3);
}

static void test()
{
    doTests("graph/islands.testcases", [](json& testcase)->bool{
        Solution s;
        vector<vector<char>> a = testcase["data"];
        int result = testcase["result"];
        int r = s.numIslands(a);
        return (result == r);
        });
}

APPEND_TO_TEST(); 
