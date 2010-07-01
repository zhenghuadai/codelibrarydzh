/*
 * =====================================================================================
 *       Filename:  testnew.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2010 02:23:47 PM
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

#include <iostream>
using namespace std;

class A{
    public:
        A(int a){ printf(" constructor 1\n");}
        A(){ printf(" constructor default\n");}
        ~A(){ printf(" ~constructor \n");}
};

int main()
{
    A* a = new A[5];
    int *i = new int[5];
    delete[] a;
    delete[] i;
    cout<<a<<endl;
    return 0;
}
