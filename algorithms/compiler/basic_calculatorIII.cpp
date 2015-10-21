/*
 * =====================================================================================
 *
 *       Filename:  basic_calculatorII.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 06:43:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
/*

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, /, (, ), operators and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
*/
#include "common.h"

namespace{

class Solution {
private:
    bool isOp(char c){
        return (c == '+' || c == '-' || c == '*' || c=='/');
    }
    
    bool islowOp(char c){
        return (c == '+' || c == '-');
    }
    
    bool ishighOp(char c){
        return (c == '*' || c == '/');
    }
    
    bool isDigital(char c){
        return (c >= '0' && c <='9'); 
    }
    
    int op2rand(char op, int oprand0, int oprand1){
        int r = 0;
        switch(op){
            case '*': r = oprand0 * oprand1; break;
            case '+': r = oprand0 + oprand1; break;
            case '-': r = oprand0 - oprand1; break;
            case '/': if(oprand1 != 0) r = oprand0 / oprand1;break;
            default:break;
        }
        return r;
    }

    void doOne(stack<int>& oprands, stack<char>& ops)
    {
        int oprand1 = oprands.top(); oprands.pop();
        int oprand0 = oprands.top(); oprands.pop();
        int r = op2rand(ops.top(), oprand0, oprand1);
        ops.pop();
        oprands.push(r);
    }

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
            }else if ( ishighOp(p[i])){
                while ((!ops.empty()) && ishighOp(ops.top())){
                    doOne(oprands, ops);
                }
                ops.push(p[i]);
                i++;
                continue;
            }else if ( islowOp(p[i])){
                while ((!ops.empty()) && isOp(ops.top())){
                    doOne(oprands, ops);
                }
                ops.push(p[i]);
                i++;
                continue;
            }else if (p[i] == '('){
                ops.push(p[i]);
                i++;
                continue;
            }else if (p[i] == ')'){
                while ((ops.top() != '(') ){
                    doOne(oprands, ops);
                }
                if (ops.top() == '('){
                    ops.pop();
                }
                i++;
            }else if( isDigital(p[i])){
                int num = 0;
                while (p[i] >= '0' && p[i] <= '9'){
                    num = num * 10 + (p[i] - '0');
                    i++;
                }
                oprands.push(num);
            }else{
                break;
            }
        }
        while ((!ops.empty()) && isOp(ops.top())){
                    doOne(oprands, ops);
        }
        int sum = oprands.top();
        return sum;
    }
};
} /// namespace

int test_calculateIII(string& exp) {
    Solution S;
    return S.calculate(exp);
}
