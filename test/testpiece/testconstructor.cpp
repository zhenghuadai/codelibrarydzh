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
        const int c;
        static int d;
        static const int e;
    public:
        A():c(100){printf("default constructor\n");}  
        A(const A& o):c(100){printf("copy constructor\n");}  
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
        void vcc()const{ printf("c:%d\n", c);}
        void vc(){ printf("c:%d\n", c);}
        void vd(){ printf("d:%d\n", d);}
        void ve(){ printf("e:%d\n", e);}

};
int A::d;
const int A::e=400;

const A operator*(const A& lhs, const A& rhs){ 
    A c;
    c.a = lhs.a * rhs.a;
    return c;
}

int main()
{
    A a, b,c;
    c = a * b;
    a.vcc();
    a.vc();
    a.vd();
    a.ve();
}
