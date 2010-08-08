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
#include "threadWrapper.h"
#include "threadPool.h"
//#include "launch.h"
THREAD_VAR ;

long long x = 0;
__thread threadX;
kernel_ret sfunc0( int x0, int y, int z )
{
	int i;
	//poptArg(int, x0, int, y, int, z);
	printf("threadX %0x\n", &threadX);
	printf("thread %d\n", x0);
	printf("thread loop %d\n", y);
	for(i=0;i<100000 ;i++)
	{
	P(tMutex);
	
	x ++;
	mV(tMutex);
	}
	return (void*) x;
	//v();
}

kernel_ret sfunc2( int x0, int y)
{
	int i;
	//poptArg(int, x0, int, y, int, z);
    printf("thread sfunc2\n");
	printf("threadX %0x\n", &threadX);
	printf("thread %d\n", x0);
	printf("thread loop %d\n", y);
	for(i=0;i<100000 ;i++)
	{
	P(tMutex);
	
	x ++;
	mV(tMutex);
	}
	return (void*) x;
	//v();
}




/*
 func_ret pfunc0(void*p)
//defineThreadFunc2(pfunc0,( int, x0, int, y, int, z))
 */
//defineThreadFunc3(pfunc0,( int(x0), int(y), int(z)))
void __attribute__((stdcall)) pfunc0( int x0, int y, int z)
{
//	poptArg3(int( x0), int( y), int( z));
	int i;
	//poptArg(int, x0, int, y, int, z);
	printf("thread %d\n", x0);
	printf("thread loop %d\n", y);
    printf("pfunc0\n");
	for(i=0;i<100000 ;i++)
	{
	P(tMutex);
	
	x ++;
	mV(tMutex);
	}
	//v();
}

#if 0
defineThreadFunc3(pfunc3_0,( pu32(x0), int(y), int(z)))
{
	poptArg3(pu32( x0), int( y), int( z));
	int i;
	printf("threadX %0x\n", &threadX);
	//poptArg(int, x0, int, y, int, z);
	printf("thread %d\n", *x0);
	printf("thread loop %d\n", y);
	for(i=0;i<100000 ;i++)
	{
	P(tMutex);
	
	x ++;
	mV(tMutex);
	}
	//v();
}
#endif

tfunc_ret pfunc1(void*p){
	int i;
	printf("thread %d\n", p);
	for(i=0;i<100000 ;i++)
	{
	P(tMutex);
	
	x ++;
	mV(tMutex);
	}
	//v();
}

tfunc_ret pfunc(void*p){
	Barrier();
	printf("threads %d\n", p);
	P(tMutex);
	x ++;
	mV(tMutex);
}


void testPool()
{
	int i=0;
	ThreadContext* c;

	initGroup(0,2);

	c = threadGroupContext[0].c;

	for(i=0;i<10;i++){
		int j=0;
#if 0
		for(j=0;j<THREAD_NUM;j++){
			launch3(j)(pfunc3_0)(&i,i,'a');
		}

		START_GROUP(0);
		FINISH_GROUP(0);
#endif
		for(j=0;j<THREAD_NUM;j++){
			launch3(j)(pfunc0)((int)(i*THREAD_NUM+j), (int)i, (int)'a');
		}

		START_GROUP(0);
		FINISH_GROUP(0);
		printf("\n");
	}
	closeGroup(0);
}

int main()
{
	void *ret;
	INIT_THREAD_VAR();
#if 0
	create_threads(pfunc, tid);
	invoke(pfunc1);
	waitall_threads();
	//system("pause");
	printf("%d\n",x);
#endif
	testPool();
	//printf("%d\n",x);
	
	slaunch3(sfunc0)((int)1,(int) 2,(int) 3);
	waitall_threads();
//	slaunch2(sfunc2)((int)1,(int) 2);
//	waitall_threads();

	printf("ret %d\n", retTable[0]);
	printf("%d\n",x);
	FREE_THREAD_VAR() ;
}
