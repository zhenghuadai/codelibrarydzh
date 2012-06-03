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
int global_i = 2;
int test1()
{
    int global_j = 2;
    double a = 1, b= 0.0, c=1;
    double *p = &c;
    try {
        int i =0;
        global_i = 20;
        global_j = 20;
        printf("m:global j %d\n", global_j);
    b = *p -c;
        printf("%f\n",  a / b);
        //Throw (char, 2);
    } CATCH(int ,a){
        printf ("exception\n");
        printf("e:global i %d\n", global_i);
        printf("e:global j %d\n", global_j);
    } CATCH(char ,a){
        printf ("exception char %d\n", a);
        printf("e:global i %d\n", global_i);
        printf("e:global j %d\n", global_j);
        Throw(char, a+1);
    } CATCHALL(...){

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

#ifdef __cplusplus
int test5()
{
    try
    {
            *(int*) 0 = 0;
    }
    catch (std::exception& e)
    {
            std::cout<< "Exception catched : " << e.what() << std::endl;
    }
    catch(...)
    {
    }
}
#endif

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
