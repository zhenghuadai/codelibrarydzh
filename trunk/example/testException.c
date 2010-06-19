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
THREAD_LOCAL    ExceptionFrame_t* ceh_stack;
int main()
{
    try {
        int i =0;
        throw (char, 2);
    } CATCH(int ,a){
        printf ("exception\n");
    } CATCH(char ,a){
        printf ("exception char\n");
    }
    endtry
}
