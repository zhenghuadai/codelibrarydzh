/*
 * =====================================================================================
 *
 *       Filename:  longest_valid_parentheses.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 03:57:34 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "common.h"
class Solution {
    enum{LEFT = 0, RIGHT =1};
    struct Node{
        int index;
        int c;
        bool match(int a) { return (c == '(' && a == ')');}
        Node(int i, int c):index(i), c(c){}
    };
public:
    int longestValidParentheses(string s) {
        std::stack<Node> cStack;
        int i = 0;
        int ret = 0;
        cStack.push(Node(-1, -1));
        for(i = 0; i<s.size(); i++){
            if(cStack.top().match(s[i])){
                cStack.pop();
            }else{
                cStack.push(Node(i, s[i]));
            }
            int curLen = i - cStack.top().index;
            if(curLen > ret) ret = curLen;
        }
        return ret;
    }
};


int test_longestValidParentheses(string& s) {
    Solution S;
    return S.longestValidParentheses(s);
}
