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
typedef struct {unsigned short tid; unsigned short gid;} threadid_t;
#define GID(threadid) ((*(threadid_t*)&threadid).gid)
#define TID(threadid) ((*(threadid_t*)&threadid).tid)
#define WARNING(x) printf(x)
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

#if defined(_MSC_VER)
#       define THREAD_LOCAL __declspec(thread)
#elif defined(__GNUC__)
#       define THREAD_LOCAL __thread
#endif

#ifdef  _PTHREAD
/****************************************************************************************/
/**************************pthread*******************************************************/
/****************************************************************************************/
#include <pthread.h>
#include <semaphore.h>
#define DEFAULT_CDECL
//typedef sem_t           sem_t;
typedef pthread_cond_t    cond_t;
typedef pthread_mutex_t   mutex_t;
typedef pthread_t         thread_t;
typedef pthread_barrier_t barrier_t;

//! declare
#define declare_sem(x)     sem_t x
#define declare_cond(x)	   pthread_cond_t x= PTHREAD_COND_INITIALIZER
#define declare_mutex(x)   pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER
#define declare_thread(x)  pthread_t x
#define declare_barrier(x) pthread_barrier_t x
//! declare end
#define sInit(x, n) sem_init(x, 0, n)

//! create
#define create_sem(m_sem, initCount, maxCount) { sem_init(m_sem, 0, initCount);}
#define create_semp(sem_handler, initCount, maxCount) {if(sem_handler == NULL) sem_handler = (sem_t*)malloc(sizeof(sem_t)); sem_init(sem_handler, 0, initCount);}
#define create_thread(pfunc, arg) ({\
        unsigned int tid = tNum; pthread_t localt;\
        /*  printf("create thread %0x\n", arg);*/\
        funcInfo_t* ft = (funcInfo_t*)arg;\
        /*  printf("\t.%0x launch %d %d\n", arg,  ((unsigned int**)(ft->esp))[0] -header, ((unsigned int**)(ft->esp))[1] - header );*/\
        int ret = pthread_create(&localt, NULL, (void *(*)(void *))pfunc, arg); \
        tTable[tNum++]=localt;\
        if(ret)printf("create thread error\n");\
        localt;\
        })

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

#define close_thread(t) if(t) {pthread_join(t, NULL); t=0;}
#define close_thread2(t) if(t) {pthread_join(t, &retTable[tid]); t=0;} // wait and get the return value of the thread

#define waitall_threads() {\
	int tid;\
	for(tid=0;tid<tNum;tid++){\
		close_thread2(tTable[tid] );\
	}\
}

#define THREAD_VAR \
thread_t tTable[THREAD_NUM*2]; \
void* retTable[THREAD_NUM*2]; \
declare_barrier(tBarrier);\
declare_mutex(tMutex);\
declare_cond(tCond);\
static int tNum=0;\
THREAD_LOCAL int active_gid=0;\
	
#define INIT_THREAD_VAR()\
pthread_barrier_init(&tBarrier, NULL, THREAD_NUM);

#define FREE_THREAD_VAR() {\
}
//! p & v
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

#define __thread_ret void* 
#ifdef DEFAULT_STDCALL
#define __kernel 	void * __attribute__((stdcall)) 
#else
#define __kernel void* 
#endif
#define STDCALL  __attribute__((stdcall))
/****************************************************************************************/
/**************************pthread*******************************************************/
/****************************************************************************************/
#else 
/****************************************************************************************/
/**************************win thread****************************************************/
/****************************************************************************************/
#include <windows.h>
#include <process.h>

#define DEFAULT_STDCALL
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

#define sInit(x, n) x= CreateSemaphore(NULL, n, 10, NULL);

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

#define close_thread(t) if(t){CloseHandle(t); t=0;}
#define close_thread2(t) if(t){GetExitCodeThread(t, (LPDWORD)&retTable[tid]); CloseHandle(t); t=0;}

#define waitall_threads() {\
	int tid=0;\
	WaitForMultipleObjects(tNum, tTable, TRUE, INFINITE);\
	for(tid=0;tid<tNum;tid++){\
		close_thread2(tTable[tid]);\
	}\
}

#define THREAD_VAR \
thread_t tTable[THREAD_NUM*2]; \
unsigned int  retTable[THREAD_NUM*2]; \
barrier_t tBarrier;\
mutex_t tMutex;\
declare_cond(tCond);\
static int tNum=0;\
THREAD_LOCAL active_gid=0;

#define INIT_THREAD_VAR()\
tBarrier= CreateEvent(NULL, TRUE, FALSE, NULL);\
tMutex= /*CreateSemaphore(NULL, 1, 1, NULL); */CreateMutex(NULL,FALSE , 0);

#define FREE_THREAD_VAR() {\
    if(tMutex) {CloseHandle(tMutex); tMutex=0;}\
	if(tBarrier) {CloseHandle(tBarrier); tBarrier=0;}\
	if(tCond) {CloseHandle(tCond); tCond=0;}\
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

#define __thread_ret unsigned WINAPI
#define __kernel unsigned WINAPI	
#define STDCALL WINAPI
//typedef  unsigned WINAPI __thread_ret ;
#endif   /* ----- #ifndef _PTHREAD  ----- */

#ifndef _INTSIZEOF 
#define _INTSIZEOF(n)  ((sizeof(n)+sizeof(long)-1)&~(sizeof(long) - 1) )
#endif

#define _tmpvar(x) tmp_ ## x 
#define tmpvar(x) _tmpvar(x)
#ifdef __cplusplus
#define ATOM(s)  for(int tmpvar(__LINE__)=0,t=(P(s),1); tmpvar(__LINE__)<1;tmpvar(__LINE__)++, (V(s))) 
#else
static THREAD_LOCAL tmp_index = 0;
#define ATOM(s)  for(tmp_index=0,(P(s),1); tmp_index<1;tmp_index++, (V(s))) 
#endif

#include "threadLauncher.h"
#endif   /* ----- #ifndef THREADWRAPPER_HEADER__INC  ----- */


