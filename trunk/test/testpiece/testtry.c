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

int main(){
    int i;
    try{
        printf("a");
    }catch(...){
        printf("catch");
    }
}
