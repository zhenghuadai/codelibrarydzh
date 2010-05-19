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

#define defaultMutex(x)\
	pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER;

#define defaultCond(x)\
	pthread_cond_t x= PTHREAD_COND_INITIALIZER;

#define defaultBarrier(x)\
	pthread_barrier_t x;

#define THREAD_VAR \
pthread_t tTable[THREAD_NUM*2]; \
defaultBarrier(tBarrier);\
defaultMutex(tMutex);\
defaultCond(tCond);\
static int tNum=0;

#define create_threads(pfunc, arg) {\
	pthread_barrier_init(&tBarrier, NULL, THREAD_NUM);\
	for(;tNum<THREAD_NUM;tNum++){\
		unsigned int tid = tNum;\
		int ret =pthread_create(&tTable[tNum], NULL, (void *(*)(void *))pfunc, arg);\
	}\
}

#define create_thread(pfunc, arg) \
{unsigned int tid = tNum; int ret = pthread_create(&tTable[tNum++], NULL, (void *(*)(void *))pfunc, arg);}

#define invoke(pfunc) \
{int ret = pthread_create(&tTable[tNum++], NULL, (void *(*)(void *))pfunc, NULL);}

#define waitall_threads() {\
	int i;\
	for(i=0;i<tNum;i++)\
		pthread_join(tTable[i], NULL);\
}

#define P(s) pthread_mutex_lock(&s); 
#define V(s) pthread_mutex_unlock(&s)
#define tP(s) pthread_mutex_trylock(&s); 
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

#define defaultMutex(x)\
	HANDLE x=0;

#define defaultCond(x)\
	HANDLE x =0;

#define defaultBarrier(x)\
	HANDLE x=0;

#define THREAD_VAR \
HANDLE tTable[THREAD_NUM*2]; \
HANDLE tBarrier;\
HANDLE tMutex;\
defaultCond(tCond);\
static int tNum=0;

#define create_threads(pfunc, arg) {\
	tMutex= CreateMutex(NULL,FALSE , 0);\
	tBarrier = CreateEvent(NULL, TRUE, FALSE, NULL);\
	for(;tNum<THREAD_NUM;tNum++){\
		unsigned int threadid;\
		unsigned int tid = tNum;\
        tTable[tNum] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, &threadid );\
	}\
}

#define create_thread(pfunc, arg) \
        {unsigned int tid = tNum; tTable[tNum++] = (HANDLE)_beginthreadex(NULL, 0, pfunc, arg, 0, NULL);}

#define invoke(pfunc) \
        {tTable[tNum++] = (HANDLE)_beginthreadex(NULL, 0, pfunc, NULL, 0, NULL);}

#define waitall_threads() {\
	int i=0;\
	WaitForMultipleObjects(tNum, tTable, TRUE, INFINITE);\
	for(i=0;i<tNum;i++){\
	CloseHandle(tTable[i]);\
	}\
	if(tMutex) CloseHandle(tMutex);\
	if(tBarrier) CloseHandle(tBarrier);\
	if(tCond) CloseHandle(tCond);\
}



#define P(s) WaitForSingleObject(s, INFINITE); 
#define V(s) ReleaseSemaphore(s, 1 ,0)
#define tP(s) pthread_mutex_trylock(&s); 
#define p() WaitForSingleObject(tMutex,INFINITE); 
#define v() ReleaseSemaphore(&tMutex, 1, 0)
#define condP(cond_s, cond_mutex) pthread_cond_wait(&cond_s, &cond_mutex);
#define condV(cond_s) pthread_cond_signal(&cond_s);
#define Barrier()  //WaitForSingleObject(tBarrier, INFINITE);

#define tfunc_ret unsigned WINAPI
#endif   /* ----- #ifndef _PTHREAD  ----- */

#endif   /* ----- #ifndef THREADWRAPPER_HEADER__INC  ----- */
