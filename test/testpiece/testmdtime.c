/*
 * =====================================================================================
 *       Filename:  testmdtime.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/18/2010 10:22:47 PM
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


#include "mdtime.h"

int main(){
U64 a ,b; 
pmdtime(0);
sleep(1);
pmdtime(1);

a= getClock();
sleep(1);
b= getClock();
printf("%ld\n", b-a);
}
