/*
 * =====================================================================================
 *       Filename:  testException.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2010 08:34:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai , djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "cexception.h"
#include <stdio.h>

THREAD_LOCAL    ExceptionFrame_t* ceh_stack;
int test1()
{
    try {
        int i =0;
        Throw (char, 2);
    } CATCH(int ,a){
        printf ("exception\n");
    } CATCH(char ,a){
        printf ("exception char %d\n", a);
        Throw(char, a+1);
    }
    endtry
}

int test2()
{
    try {
        int i =0;
        test1();
    } CATCH(int ,a){
        printf ("exception\n");
    } CATCH(char ,a){
        printf ("exception char %d\n", a);
        Throw(char, a+1);
    }
    endtry
}


int test()
{
  
    try {
        int i =0;
        test2();
    } CATCH(int ,a){
        printf ("exception\n");
    } CATCH(char ,a){
        printf ("exception char %d\n", a);
        Throw(char, a+1);
    }
    endtry 
}

int main()
{

    try {
        int i =0;
        test();
    } CATCH(int ,a){
        printf ("exception\n");
    } CATCH(char ,a){
        printf ("exception char %d\n", a);
    }
    endtry
}
