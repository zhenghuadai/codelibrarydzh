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

#ifdef  _PTHREAD

typedef barrier_t GroupBarrier_t;
typedef void*  (*tkernel_t )(void *arg);
#define creatBarrier( tBarrier) \
	pthread_barrier_init(&tBarrier, NULL, thread_num +1)

#define START_GROUP(gid)  pthread_barrier_wait(&(threadGroupContext[gid].work_barrier));
#define FINISH_GROUP(gid) pthread_barrier_wait(&(threadGroupContext[gid].done_barrier));

#define START_TASK(gid, tid)  sV((threadGroupContext[gid].c[tid].work_sem));
#define FINISH_TASK(gid, tid) sP((threadGroupContext[gid].c[tid].done_sem));
#define START_GROUP2(gid)  {int tid_i; for(tid_i=0;tid_i<threadGroupContext[gid].group_size; tid_i++) START_TASK(gid, tid_i);} 
#define FINISH_GROUP2(gid) {int tid_i; for(tid_i=0;tid_i<threadGroupContext[gid].group_size; tid_i++) FINISH_TASK(gid, tid_i);} 

/****************************************************************************************/
/**************************pthread*******************************************************/
/****************************************************************************************/
#else 
/****************************************************************************************/
/**************************win thread****************************************************/
/****************************************************************************************/

typedef sem_t GroupBarrier_t;
typedef unsigned  (__stdcall *tkernel_t )(void *arg);
#define START_GROUP(gid) ReleaseSemaphore(threadGroupContext[gid].work_barrier, threadGroupContext[gid].group_size, 0);
#define FINISH_GROUP(gid) {\
for(j=0; j<threadGroupContext[gid].group_size; j++)\
			sP(threadGroupContext[0].done_barrier);\
}

#define START_TASK(c)  sP(threadGroupContext[gid].work_sem)
#define FINISH_TASK(c) sV(threadGroupContext[gid].done_sem );

#define creatBarrier(tBarrier) tBarrier= CreateSemaphore(NULL, 0, INT_MAX, NULL)

#endif   /* ----- #ifndef _PTHREAD  ----- */

enum {thread_exit = 0, thread_busy = -1, thread_idle = 1};
enum {group_exit = 0,  group_busy = -1,  group_idle = 1};

typedef struct ThreadContext{
	//thread_t thread;
    int status;
	int groupID;
	sem_t work_sem;
	sem_t done_sem;
	void *ret;
	void *arg;
    union{
        struct{
            tkernel_t func;
            int argSize;
            char kArg[128];
        };
        task_t task;
    };
}ThreadContext, *pThreadContext;

typedef struct ThreadGroupContext{
    GroupBarrier_t work_barrier;
    GroupBarrier_t done_barrier;
    int group_size;
    thread_t* tTable;
    ThreadContext* c;
    int status;
}ThreadGroupContext;

static ThreadGroupContext threadGroupContext[32]={0};

/*################################################################################################  */
/*################################################################################################  */
/*####################        method 1          ##################################################  */
/*################################################################################################  */
/*################################################################################################  */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  thread_func
 *  Description:  the thread pool template,  when it is woken up, it will run c->func
 *  	  Input:  v: the ThreadContext pointer 
 *       Output:  TBD
 *      Example:  
 * =====================================================================================
 */
static tfunc_ret  thread_func(void *v){
    ThreadContext *c= (ThreadContext *)v;
    ThreadGroupContext* groupCtx = & threadGroupContext[c->groupID ];
    for(;;){
        START_GROUP(c->groupID); //sP(groupCtx->work_sem); 
        if ((!c->func  )|| (groupCtx->status == group_exit))	break;		 
        //		   c->ret= c->func((void*)c->arg); 
        call_stdfunc(c->func, c->arg, c->argSize);
        FINISH_GROUP(c->groupID);//sV(groupCtx->done_sem );
    }
    return 0;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initGroup
 *  	  Input:  
 *  	         gid:        thre group id that you want to initialize
 *  	         thread_num: the number of threads that you want to create
 *       Output: TBD
 *      Example:  initGroup(0, 2)
 * =====================================================================================
 */
static int initGroup( int gid, int thread_num)
{
    ThreadGroupContext* groupCtx=threadGroupContext;
    ThreadContext* c= (ThreadContext* )malloc(sizeof(ThreadContext)*THREAD_NUM);
    creatBarrier(groupCtx[gid].work_barrier/*c[0].work_sem*/ );

    creatBarrier(groupCtx[gid].done_barrier/*c[0].done_sem */);

    groupCtx[gid].tTable = (thread_t*) malloc(sizeof(thread_t)*thread_num);
    memset( groupCtx[gid].tTable, 0, sizeof(thread_t)*thread_num);

    groupCtx[gid].group_size = thread_num;
    groupCtx[gid].c=c;
    groupCtx[gid].status = 1;

    {
        int i;
        for(i=0;i<thread_num;i++){ // init thread context
            c[i].groupID = gid; 
        }
    }

    create_nthreads(groupCtx[gid].tTable,(thread_num), thread_func,&c[tid]);
    return 0; 
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  closeGroup
 *  	  Input:  gid:  the group that you want to close
 *       Output:
 *      Example:  closeGroup(0)
 * =====================================================================================
 */
void closeGroup(int gid) {
    int i;
    threadGroupContext[gid].status=0;
    START_GROUP(gid);
    for(i=0;i<threadGroupContext[gid].group_size;i++){
        close_thread(threadGroupContext[gid].tTable[i]);
    }
    free(threadGroupContext[gid].c);
}

/*################################################################################################  */
/*################################################################################################  */
/*#####################        method 2         ##################################################  */
/*################################################################################################  */
/*################################################################################################  */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  thread_func2
 *  Description:  the thread pool template,  when it is woken up, it will run c->func
 *  	  Input:  v: the ThreadContext pointer 
 *       Output:  TBD
 *      Example:  
 * =====================================================================================
 */
static tfunc_ret  thread_func2(void *v){
    ThreadContext *c= (ThreadContext *)v;
    ThreadGroupContext* groupCtx = & threadGroupContext[c->groupID ];
    for(;;){
        sP(c->work_sem);
        if(c->status == thread_exit || groupCtx->status == group_exit) break;
        if ((c->func  )){		 
            c->status = thread_busy;
            call_stdfunc(c->func, c->arg, c->argSize);
            c->func = NULL;
            c->status = thread_idle;
        }
        sV(c->done_sem);
    }
    return 0;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initGroup
 *  	  Input:  
 *  	         gid:        thre group id that you want to initialize
 *  	         thread_num: the number of threads that you want to create
 *       Output: TBD
 *      Example:  initGroup(0, 2)
 * =====================================================================================
 */
static int initGroup2( int gid, int thread_num)
{
    ThreadGroupContext* groupCtx=threadGroupContext;
    ThreadContext* c= (ThreadContext* )malloc(sizeof(ThreadContext)*THREAD_NUM);
    creatBarrier(groupCtx[gid].work_barrier/*c[0].work_sem*/ );

    creatBarrier(groupCtx[gid].done_barrier/*c[0].done_sem */);

    groupCtx[gid].tTable = (thread_t*) malloc(sizeof(thread_t)*thread_num);
    memset( groupCtx[gid].tTable, 0, sizeof(thread_t)*thread_num);

    groupCtx[gid].group_size = thread_num;
    groupCtx[gid].c=c;
    groupCtx[gid].status = 1;

    {
        int i;
        for(i=0;i<thread_num;i++){ // init thread context
            c[i].groupID = gid; 
            c[i].status = thread_idle;
            create_sem(&c[i].work_sem, 0, 1);
            create_sem(&c[i].done_sem, 0, 1);
        }
    }

    create_nthreads(groupCtx[gid].tTable,thread_num, thread_func2,&c[tid]);
    return 0; 
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  closeGroup2
 *  	  Input:  gid:  the group that you want to close
 *       Output:
 *      Example:  closeGroup(0)
 * =====================================================================================
 */
void closeGroup2(int gid) {
    int i;
    threadGroupContext[gid].status=group_exit;
    START_GROUP2(gid);
    for(i=0;i<threadGroupContext[gid].group_size;i++){
        close_thread(threadGroupContext[gid].tTable[i]);
        sem_destroy(&threadGroupContext[gid].c[i].work_sem);
        sem_destroy(&threadGroupContext[gid].c[i].done_sem);
    }
    free(threadGroupContext[gid].c);
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getIdleThread
 *  Description:  
 * =====================================================================================
 */
int getIdleThread(int gid){
    int i;
    ThreadGroupContext* groupCtx=threadGroupContext;
    for(i =0;i<groupCtx[gid].group_size ;i++){
        if ( groupCtx[gid].c[i].status== thread_idle) return i;
    }
    return -1;
}

#endif   /* ----- #ifndef THREAD_POOL_HEADER__INC  ----- */
