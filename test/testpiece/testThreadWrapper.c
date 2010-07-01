/*
 * =====================================================================================
 *
 *       Filename:  testThreadWrapper.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/17/2010 06:39:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#define THREAD_NUM 2
#include "pthreadWrapper.h"
THREAD_VAR ;

int x = 0;
tfunc_ret  pfunc1(void*p){
	printf("thread %d\n", p);
	p();	//P(tMutex);
	x ++;
	//V(tMutex);
	v();
}

void* pfunc(void*p){
	Barrier();
	printf("thread %d\n", p);
	P(tMutex);
	x ++;
	V(tMutex);
}

int main()
{
	INIT_THREAD_VAR();
	create_threads(pfunc, tid);
	invoke(pfunc1);
	waitall_threads();
	printf("%d\n",x);
}
