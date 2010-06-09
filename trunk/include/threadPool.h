/*
* =====================================================================================
*
*       Filename:  threadgroup.h
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

#ifndef  THREAD_POOL_HEADER__INC
#define  THREAD_POOL_HEADER__INC

#include "threadWrapper.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	void* f;
	int argSize;
	char esp[128];
}funcInfo_t;

static funcInfo_t global_funcInfo;


#ifdef  _PTHREAD

typedef barrier_t GroupBarrier_t;
typedef void*  (*tkernel_t )(void *arg);
#define createWaitingSem( tBarrier) \
	pthread_barrier_init(&tBarrier, NULL, thread_num + 1)

#define START_GROUP(gid)  pthread_barrier_wait(&(threadGroupContext[gid].work_sem));
#define FINISH_GROUP(gid) pthread_barrier_wait(&(threadGroupContext[gid].done_sem));
#define START_TASK(gid)  pthread_barrier_wait(&(threadGroupContext[gid].work_sem));
#define FINISH_TASK(gid) pthread_barrier_wait(&(threadGroupContext[gid].done_sem));

static void* thread_func_g(void*p){
	funcInfo_t* ft = (funcInfo_t*)p;
	__asm__(
	"subl %%ecx, %%esp\n"
	"movl %%esp, %%edi\n"
	"rep movsb\n"
	"call *%%eax\n"
	:
	:"a"(ft->f),"c"(ft->argSize), "S"(ft->esp)
	:"%edi");
}


/****************************************************************************************/
/**************************pthread*******************************************************/
/****************************************************************************************/
#else 
/****************************************************************************************/
/**************************win thread****************************************************/
/****************************************************************************************/

typedef sem_t GroupBarrier_t;
typedef unsigned  (__stdcall *tkernel_t )(void *arg);
#define START_GROUP(gid) ReleaseSemaphore(threadGroupContext[gid].work_sem, threadGroupContext[gid].group_size, 0);
#define FINISH_GROUP(gid) {\
for(j=0; j<threadGroupContext[gid].group_size; j++)\
			sP(threadGroupContext[0].done_sem);\
}

#define START_TASK(gid) sP(threadGroupContext[gid].work_sem)
#define FINISH_TASK(gid) sV(threadGroupContext[gid].done_sem );

#define createWaitingSem(tBarrier) tBarrier= CreateSemaphore(NULL, 0, INT_MAX, NULL)
kernel_ret thread_func_g(void*p){
	funcInfo_t* ft = (funcInfo_t*)p;
	unsigned int f = (unsigned int)ft->f;
	unsigned int argSize = (unsigned int)ft->argSize;
	unsigned int stack = (unsigned int)ft->esp;
	__asm{ 
			__asm push esi
			__asm push edi
			__asm mov eax, f
			__asm mov ecx,  argSize
			__asm mov esi, stack

			__asm sub esp, ecx
			__asm mov edi, esp
			__asm rep movsb
			__asm call eax

			__asm pop edi
			__asm pop esi
 
	}
}


#endif   /* ----- #ifndef _PTHREAD  ----- */


typedef struct ThreadContext{

	thread_t thread;
	GroupBarrier_t work_sem;
	GroupBarrier_t done_sem;
	tkernel_t func;
	void *arg;
	void *ret;
	int groupID;
	char kArg[128];
}ThreadContext, *pThreadContext;

typedef struct ThreadGroupContext{
	GroupBarrier_t work_sem;
	GroupBarrier_t done_sem;
	int group_size;
	thread_t* tTable;
	ThreadContext* c;
	int running;
}ThreadGroupContext;

static ThreadGroupContext threadGroupContext[32]={0};



static tfunc_ret  thread_func(void *v){
	ThreadContext *c= (ThreadContext *)v;
	ThreadGroupContext* groupCtx = & threadGroupContext[c->groupID ];
	for(;;){
		START_TASK(c->groupID); //sP(groupCtx->work_sem); 
		if ((!c->func  )|| (groupCtx->running == 0))	break;		 
		   c->ret= c->func((void*)c->arg); 
		FINISH_TASK(c->groupID);//sV(groupCtx->done_sem );
	}
	return 0;
}

static int initGroup( int gid, int thread_num)
{
	ThreadGroupContext* groupCtx=threadGroupContext;
	ThreadContext* c= (ThreadContext* )malloc(sizeof(ThreadContext)*THREAD_NUM);
	createWaitingSem(groupCtx[gid].work_sem /*c[0].work_sem*/ );

	createWaitingSem(groupCtx[gid].done_sem /*c[0].done_sem */);

	groupCtx[gid].tTable = (thread_t*) malloc(sizeof(thread_t)*thread_num);

	groupCtx[gid].group_size = thread_num;
	groupCtx[gid].c=c;
	groupCtx[gid].running = 1;
	
	{
		int i;
		for(i=0;i<thread_num;i++)
			c[i].groupID = gid; 
	}

	create_nthreads(groupCtx[gid].tTable,thread_num, thread_func,&c[tid]);
	return 0; 
}

void closeGroup(int gid) {
	int i;
	threadGroupContext[gid].running=0;
	START_GROUP(gid)
	for(i=0;i<threadGroupContext[gid].group_size;i++){
		close_thread(threadGroupContext[gid].tTable[i]);
	}
}


#endif   /* ----- #ifndef THREAD_POOL_HEADER__INC  ----- */
