/*
 * =====================================================================================
 *       Filename:  testconstructor.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/08/2010 07:30:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai , djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 *     Copyright (c) 2010, Zhenghua Dai. All rights reserved.
 * =====================================================================================
 */

#include <stdio.h>

class A
{
    public:
        int a;
        int b;
    public:
        A(){printf("default constructor\n");}  
        A(const A& o){printf("copy constructor\n");}  
    public:
        A operator*(const A& o){
            A c;
            c.a = this->a * o.a;
            printf("operator *\n");
            return c;
        }
        A operator=(const A& o){
            printf("set\n");
        }
};

const A operator*(const A& lhs, const A& rhs){ 
    A c;
    c.a = lhs.a * rhs.a;
    return c;
}

int main()
{
    A a, b,c;
    c = a * b;
}
