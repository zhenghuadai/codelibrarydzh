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

#include <pthread.h>

#define defaultMutex(x)\
	pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER;

#define defaultCond(x)\
	pthread_cond_t x= PTHREAD_COND_INITIALIZER;

#define THREAD_VAR \
pthread_t tTable[THREAD_NUM]; \
pthread_barrier_t tBarrier;\
pthread_mutex_t tMutex=PTHREAD_MUTEX_INITIALIZER;\
defaultCond(tCond);\
static int tNum=0;

#define create_threads(pfunc, arg) {\
	pthread_barrier_init(&tBarrier, NULL, THREAD_NUM);\
	for(;tNum<THREAD_NUM;tNum++){\
		int ret =pthread_create(&tTable[tNum], NULL, (void *(*)(void *))pfunc, arg);\
	}\
}

#define create_thread(pfunc, arg) \
{int ret = pthread_create(&tTable[tNum++], NULL, (void *(*)(void *))pfunc, arg);}

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
#endif   /* ----- #ifndef THREADWRAPPER_HEADER__INC  ----- */
