/*
 * =====================================================================================
 *       Filename:  testfloat.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/24/2010 04:14:13 PM
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
#include <stdlib.h>


int main(int argc, char** argv)
{
    float a;
    int *p = (int*)&a;
    int exp;
    if(argc >1)
        a= atof(argv[1]);
    exp =  ((*p & (0xFF<<23)) >> 23) - 127;
    printf("%d\n", exp);
    a = 34.0;
    printf("%0x\n", *p);
    a = - 34.0;
    printf("%0x\n", *p);
}
