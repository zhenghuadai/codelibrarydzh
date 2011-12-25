/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/09/2011 09:49:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include  "dmthread.h" 
#include <math.h>

int is_prime(int n)
{
    int i=0; 
    int n2 = n/2;
    for(i =2;i< n2; i++){
        int ret = n % i;
        if(ret == 0)
            return 0;
    }
    return 1;
}

void f2(void* p)
{
    int i;
    for( i= (int)p ; i< (size_t)p + 100000; i++){
        if(is_prime(i)){
            myprintf( " %ld, %d\n " ,  (size_t)p , i); 
        }
    }
}


void f1(void* p)
{
    int i;
    for( i= (int)p ; i< (size_t)p + 100000; i++){
        {
            myprintf( " %ld, %d\n " ,  (size_t)p , i); 
            //usleep(1);
        }
    }
}

int main(int argc,char **argv)
{
    //reg_thread(f0,  0 );
    reg_thread(f1,  (void*)0 );
    reg_thread(f1,  (void*)100000 );
    reg_thread(f1,  (void*)200000 );
    reg_thread(f1,  (void*)300000 );
    //setTimer();
    //f1((void*)400000);
    //sleep(1);
    dmthread_join();
    exit(0);
}
