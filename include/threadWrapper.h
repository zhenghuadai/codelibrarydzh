/*
 * =====================================================================================
 *
 *       Filename:  threadWrapper.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/17/2010 08:26:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  THREADWRAPPER_HEADER__INC
#define  THREADWRAPPER_HEADER__INC

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef unsigned char *pu8;
typedef unsigned short *pu16;
typedef unsigned int *pu32;
typedef unsigned long long *pu64;
typedef float *pf32;
typedef double *pf64;
typedef char *pi8;
typedef short *pi16;
typedef int *pi32;
typedef long long *pi64;
#ifndef THREAD_NUM
#define THREAD_NUM 2
#endif


#if (!defined(_PTHREAD)) && (!defined(_WINTHREAD))
	#if defined(__GNUC__)
		#define _PTHREAD
	#elif defined(_MSC_VER)
		#define _WINTHREAD 
	#endif
#endif

#ifdef  _PTHREAD
#include <pthread.h>
#include <semaphore.h>
//typedef sem_t           sem_t;
typedef pthread_cond_t    cond_t;
typedef pthread_mutex_t   mutex_t;
typedef pthread_t         thread_t;
typedef pthread_barrier_t barrier_t;

#define declare_sem(x)     sem_t x
#define declare_cond(x)	   pthread_cond_t x= PTHREAD_COND_INITIALIZER
#define declare_mutex(x)   pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER
#define declare_thread(x)  pthread_t x
#define declare_barrier(x) pthread_barrier_t x

#define create_thread(pfunc, arg) \
{unsigned int tid = tNum; int ret = pthread_create(&tTable[tNum++], NULL, (void *(*)(void *))pfunc, arg);}

#define create_threads(pfunc, arg) {\
	for(;tNum<THREAD_NUM;tNum++){\
		unsigned int tid = tNum;\
		int ret =pthread_create(&tTable[tid], NULL, (void *(*)(void *))pfunc, arg);\
	}\
}

#define create_nthreads(tTable, n, pfunc, arg) {\
	int tid=0;\
    for(tid=0;tid<n;tid++){\
       int ret =pthread_create(&tTable[tid], NULL, (void *(*)(void *))pfunc, arg);\
	}\
}

#define invoke(pfunc) \
{int ret = pthread_create(&tTable[tNum++], NULL, (void *(*)(void *))pfunc, NULL);}

#define close_thread(t) pthread_join(t, NULL);

#define waitall_threads() {\
	int i;\
	for(i=0;i<tNum;i++)\
		close_thread(tTable[i] );\
}

#define THREAD_VAR \
thread_t tTable[THREAD_NUM*2]; \
declare_barrier(tBarrier);\
declare_mutex(tMutex);\
declare_cond(tCond);\
static int tNum=0;\
	
#define INIT_THREAD_VAR()\
pthread_barrier_init(&tBarrier, NULL, THREAD_NUM);

#define FREE_THREAD_VAR() {\
}

#define P(s) pthread_mutex_lock(&s)
#define V(s) pthread_mutex_unlock(&s)

#define mP(s) pthread_mutex_lock(&s)
#define mV(s) pthread_mutex_unlock(&s)

#define sP(s) sem_wait(&s)
#define sV(s) sem_post(&s)
#define sVn(s,n) {int i; for(i=0;i<n,i++)sem_post(&s);}

#define tryP(s) pthread_mutex_trylock(&s); 
#define p() pthread_mutex_lock(&tMutex); 
#define v() pthread_mutex_unlock(&tMutex)
#define condP(cond_s, cond_mutex) pthread_cond_wait(&cond_s, &cond_mutex);
#define condV(cond_s) pthread_cond_signal(&cond_s);
#define Barrier() pthread_barrier_wait(&tBarrier);

#define tfunc_ret void* 
/****************************************************************************************/
/**************************pthread*******************************************************/
/****************************************************************************************/
#else 
/****************************************************************************************/
/**************************win thread****************************************************/
/****************************************************************************************/
#include <windows.h>
#include <process.h>

typedef HANDLE sem_t;
typedef HANDLE cond_t;
typedef HANDLE mutex_t;
typedef HANDLE thread_t;
typedef HANDLE barrier_t;

#define declare_sem(x)     sem_t x=0
#define declare_cond(x)    cond_t x=0
#define declare_mutex(x)   mutex_t x=0
#define declare_thread(x)  thread_t x=0
#define declare_barrier(x) barrier_t x=0

#define create_thread(pfunc, arg) \
        {unsigned int tid = tNum; tTable[tNum++] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, NULL);}

#define create_threads(pfunc, arg) {\
	for(;tNum<THREAD_NUM;tNum++){\
		unsigned int threadid;\
		unsigned int tid = tNum;\
        tTable[tNum] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, &threadid );\
	}\
}

#define create_nthreads(tTable, n, pfunc, arg) {\
	int tid=0;\
    for(tid=0;tid<n;tid++){\
		unsigned int threadid;\
        tTable[tid] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, &threadid );\
	}\
}

#define invoke(pfunc) \
        {tTable[tNum++] = (HANDLE)_beginthreadex(NULL, 0, pfunc, NULL, 0, NULL);}

#define close_thread(t) CloseHandle(t);

#define waitall_threads() {\
	int i=0;\
	WaitForMultipleObjects(tNum, tTable, TRUE, INFINITE);\
	for(i=0;i<tNum;i++){\
		close_thread(tTable[i]);\
	}\
}

#define THREAD_VAR \
thread_t tTable[THREAD_NUM*2]; \
barrier_t tBarrier;\
mutex_t tMutex;\
declare_cond(tCond);\
static int tNum=0;

#define INIT_THREAD_VAR()\
tBarrier= CreateEvent(NULL, TRUE, FALSE, NULL);\
tMutex= /*CreateSemaphore(NULL, 1, 1, NULL); */CreateMutex(NULL,FALSE , 0);

#define FREE_THREAD_VAR() {\
    if(tMutex) CloseHandle(tMutex);\
	if(tBarrier) CloseHandle(tBarrier);\
	if(tCond) CloseHandle(tCond);\
}

#define P(s) WaitForSingleObject(s, INFINITE); 
#define V(s) ReleaseSemaphore(s, 1 ,0)

#define mP(s) WaitForSingleObject(s, INFINITE); 
#define mV(s) ReleaseMutex(s)

#define sP(s) WaitForSingleObject(s, INFINITE); 
#define sV(s) ReleaseSemaphore(s, 1 ,0)
#define sVn(s,n) ReleaseSemaphore(s, n ,0)

#define trymP(s)  

#define p() WaitForSingleObject(tMutex,INFINITE); 
#define v() ReleaseSemaphore(&tMutex, 1, 0)

#define condP(cond_s, cond_mutex) 
#define condV(cond_s) 
#define Barrier()  //WaitForSingleObject(tBarrier, INFINITE);

#define tfunc_ret unsigned WINAPI
//typedef  unsigned WINAPI tfunc_ret ;
#endif   /* ----- #ifndef _PTHREAD  ----- */
/************************************************************************************
 *
 *the Launcher
 *
 ***********************************************************************************/
#define fArgTypename(f) f##Arg_t
#define structname(a, b, c)  struct__ ## a ## b ## c

#define AAAint(x) int
#define BBBint(x) x 
#define AAApu32(x) pu32 
#define BBBpu32(x) x 

#define AAA(a) AAA##a
#define BBB(a) BBB##a  // BBB(int(a))
#define structname_mid_second(a, b, c) structname(a, b, c)
#define structname_mid(a, b, c) structname_mid_second(a, b, c)
#define structname_pre(a, b, c) structname_mid( AAA(a), AAA(b), AAA(c)) 

#define definethreadf(name, arg) \
typedef structname_pre arg name##Arg_t;\
tfunc_ret name(void*p)

#define defineArg(a, b, c)\
typedef struct{\
		a arg1;	\
		b arg2;	\
		c arg3;	\
} structname(a,b,c);


#define poptArg( a, b,c)\
AAA(a) BBB(a) = ((structname_pre(a,b,c)*)p)->arg1;\
AAA(b) BBB(b) = ((structname_pre(a,b,c)*)p)->arg2;\
AAA(c) BBB(c) = ((structname_pre(a,b,c)*)p)->arg3 

#define pushtArg(a, b, c)\
pArg->arg1=a;\
pArg->arg2=b;\
pArg->arg3=c;\
}\
}

#define launchfunc( pfuncKernel) c[tid].func = pfuncKernel; {\
fArgTypename(pfuncKernel)* pArg = (fArgTypename(pfuncKernel)*)kArg[tid];  c[tid].arg= (void*)pArg; pushtArg 
#define launch(tid0) { int tid = tid0; launchfunc 
			
#if 0
#define structname2(at,a, bt,  b,ct, c)  struct ## at ## bt ## ct
#define definethreadf0(name, para1t, para1, para2t, para2, para3t, para3)\
typedef structname(para1t, para2t, para3t) name##Arg_t; \
tfunc_ret name(void* p)

#define definethreadf2(name, arg) \
typedef structname2 arg name##Arg_t;\
tfunc_ret name(void*p)
#define launch(tid0, pfuncKernel) { int tid = tid0; c[tid].func = pfuncKernel; c[tid].arg= (void*)kArg[tid]; pushtArg

#define poptArg( at,a, bt,b, ct, c)\
at a = ((structname(at,bt,ct)*)p)->arg1;\
bt b = ((structname(at,bt,ct)*)p)->arg2;\
ct c = ((structname(at,bt,ct)*)p)->arg3;\

#define poptArg0(type, a, b, c)\
a = ((type*)p)->arg1;\
b = ((type*)p)->arg2;\
c = ((type*)p)->arg3;\


#endif
/************************************************************************************
 *
 *the Launcher end
 *
 ***********************************************************************************/

#endif   /* ----- #ifndef THREADWRAPPER_HEADER__INC  ----- */
