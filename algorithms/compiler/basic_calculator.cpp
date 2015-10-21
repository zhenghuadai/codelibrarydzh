/*
 * =====================================================================================
 *
 *       Filename:  basic_calculator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 06:34:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
/*
https://leetcode.com/problems/basic-calculator/

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23
*/

#include "common.h"
namespace{

class Solution {
public:
    int calculate(string s) {
        int i = 0;
        const char* p = s.c_str();
        stack<int> oprands;
        stack<char> ops;
        while (i< s.size()){
            if (p[i] == ' '){
                i++;
                continue;
            }else if (p[i] == '(' || p[i] == '+' || p[i] == '-'){
                ops.push(p[i]);
                i++;
                continue;
            }
            else if (p[i] == ')'){
                if (ops.top() == '('){
                    ops.pop();
                }
                i++;
            }
            else {
                int num = 0;
                while (p[i] >= '0' && p[i] <= '9'){
                    num = num * 10 + (p[i] - '0');
                    i++;
                }
                oprands.push(num);
            }
            while ((!ops.empty()) && (ops.top() == '+' || ops.top() == '-')){
                int oprand1 = oprands.top(); oprands.pop();
                int oprand0 = oprands.top(); oprands.pop();
                int r = (ops.top() == '+') ? (oprand0 + oprand1) : (oprand0 - oprand1);
                ops.pop();
                oprands.push(r);
            }
        }
        int sum = oprands.top();
        return sum;
    }
};
}/// namespace

int test_calculate(string& s) {
    Solution S;
    return S.calculate(s);
}
