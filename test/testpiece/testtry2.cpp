/*
 * =====================================================================================
 *       Filename:  testtry.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2010 03:11:07 PM
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
#include <stdio.h>
using namespace std;
class A{
    public:
    A(){ printf("construcotr\n");}
    ~A(){ printf("deconstrucotr\n");}
    void print(){printf("printf\n");}
};
int main(){
    int i;
    try{
        A c;
        try{
            A b;
            try{
                A a;
                throw 1;
                a.print();
                printf("a");
            }catch(...){
                printf("catch a \n");
                throw;
            }
        }catch(...){
            printf("catch b\n");
//            throw;
        }
    }catch(...){
        printf("catch c\n");
    }
}
