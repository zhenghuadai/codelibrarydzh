
#ifndef  THREADLAUNCHER_HEADER__INC
#define  THREADLAUNCHER_HEADER__INC
#include "stdio.h"
#include "stdlib.h"
///////////////// public ////////////////////////////////////////
#define pushArgtoStack1( a00)	push2stack(a00); 
#define pushArgtoStack2( a00, a01)	pushArgtoStack1(a00) push2stack(a01); 
#define pushArgtoStack3( a00, a01, a02)	pushArgtoStack2(a00,a01) push2stack(a02); 
#define pushArgtoStack4( a00, a01, a02, a03)	pushArgtoStack3(a00,a01,a02) push2stack(a03); 
#define pushArgtoStack5( a00, a01, a02, a03,a04)	pushArgtoStack4(a00,a01,a02,a03) push2stack(a03); 
#define pushArgtoStack6( a00, a01, a02, a03,a04,a05)	pushArgtoStack5(a00,a01,a02,a03,a04) push2stack(a03); 
/******************************************************************************
 *                                                                            *
 ***************************** launch(launch) ****************************    *
 * Function: copy the task to thread.                                         *
 ******************************************************************************/
#define launchfunc( pfuncKernel, argNum) c[tid].func = (tkernel_t) pfuncKernel; {\
        char* pcur=(char*)c[tid].kArg;  c[tid].arg= (void*)pcur; pushtArg##argNum
#define launchheader { ThreadContext*c = threadGroupContext[active_gid].c;int tid = tid0;
#define launchtailer 	c[tid].argSize = pcur - (char*) c[tid].arg;}}
//////////////////// 0 args ////////////////////////////////////////////////////
#define pushtArg0()\
}\
}

#define launchfunc0( pfuncKernel) c[tid].func = pfuncKernel; {\
	char* pcur=(char*)c[tid].kArg;  c[tid].arg= (void*)pcur; pushtArg0 
#define launch0(tid0) { ThreadContext*c = threadGroupContext[active_gid].c;int tid = tid0; launchfunc0  
	
//////////////////// 2 args ////////////////////////////////////////////////////
#define pushtArg2(a00,a01)\
	push2stack(a00); \
	push2stack(a01); \
	c[tid].argSize = pcur - (char*) c[tid].arg;\
}\
}

#define launchfunc2( pfuncKernel) c[tid].func = pfuncKernel; {\
	char* pcur=(char*)c[tid].kArg;  c[tid].arg= (void*)pcur; pushtArg2 
#define launch2(tid0) {ThreadContext*c = threadGroupContext[active_gid].c; int tid = tid0; launchfunc2  
	
//////////////////// 3 args ////////////////////////////////////////////////////
#define pushtArg3(a00,a01,a02)\
	push2stack(a00); \
	push2stack(a01); \
	push2stack(a02); \
	c[tid].argSize = pcur - (char*) c[tid].arg;\
}\
}

#define launchfunc3( pfuncKernel) launchfunc( pfuncKernel, 3)
#define launch3(tid0) {ThreadContext*c = threadGroupContext[active_gid].c; int tid = tid0; launchfunc3  
	
//////////////////// 5 args ////////////////////////////////////////////
/////////////////// 6 args ////////////////////////////////////////////////////
#define pushtArg6(a00,a01,a02,a03,a04,a05)\
    pushArgtoStack6(a00,a01,a02,a03,a04,a05)    launchtailer

#define launchfunc6( pfuncKernel) launchfunc( pfuncKernel, 6)
#define launch6(tid0) { launchheader launchfunc6  

//////////////////// 16 args ////////////////////////////////////////////////////
#define pushtArg16(a00,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12,a13,a14,a15)\
	push2stack(a00); \
	push2stack(a01); \
	push2stack(a02); \
	push2stack(a03); \
	push2stack(a04); \
	push2stack(a05); \
	push2stack(a06); \
	push2stack(a07); \
	push2stack(a08); \
	push2stack(a09); \
	push2stack(a10); \
	push2stack(a11); \
	push2stack(a12); \
	push2stack(a13); \
	push2stack(a14); \
	push2stack(a15); \
	c[tid].argSize = pcur - (char*) c[tid].arg;\
}\
}

#define launchfunc16( pfuncKernel) c[tid].func = pfuncKernel; {\
	char* pcur=(char*)c[tid].kArg;  c[tid].arg= (void*)pcur; pushtArg16 
#define launch16(tid0) {ThreadContext*c = threadGroupContext[active_gid].c; int tid = tid0; launchfunc16  
/******************************************************************************
 *                                                                            *
 ***************************** launch a single function (slaunch) *************
 * Function: create a new thread and execute the task                         *
 ******************************************************************************/
typedef struct{
    union{
        int flag;
        void* ret;
    };
    union{
        void* f;
        void* func;
    };
	int argSize;
    union{
        char esp[128];
        char arg[128];
    };
}funcInfo_t;
typedef funcInfo_t task_t;
enum{mem_stack=0 ,mem_heap=1};
inline task_t* create_task(){
    task_t* t = (task_t*)calloc(sizeof(task_t),1);
    t->flag=mem_heap;
    return t;
}
static THREAD_LOCAL funcInfo_t global_funcInfo;

#ifdef _PTHREAD
#define push2stack(v) {(*(typeof(v)*)pcur)=v; pcur += _INTSIZEOF(typeof(v));}
/** 
--- -----------  ---
EBP UPPER EBP    ESP
--- -----------  ---
    RET ADDRESS
    -----------
    ARG0
    -----------
    ARG1
    -----------
    ...
    -----------
    ARGn
    -----------
*/

#if __WORDSIZE == 32
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  call_stdfunc
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  call_stdfunc
 * =====================================================================================
 */
inline void call_stdfunc(void* func, int argSize, void* arg)
{
    __asm__(
            "subl %%ecx, %%esp\n"
            "movl %%esp, %%edi\n"
            "rep movsb\n"
            "call *%%eax\n"
            :
            :"a"(func),"c"(argSize), "S"(arg)
            :"%edi");
    //   __asm__("addl %0, %%esp\n"::"r"(ft->argSize)); /* if not stdcall, do this.
    //   Beacause, the stdcall will clean up the stack itself.
    //             the cdecl will not. So we have to clean the stack after cdecl call.*/
}

inline void call_cdeclfunc(void* func, int argSize, void* arg)
{
    __asm__ __volatile__ (
            "subl %%ecx, %%esp\n"
            "movl %%esp, %%edi\n"
            "rep movsb\n"
            "call *%%eax\n"
            :
            :"a"(func),"c"(argSize), "S"(arg)
            :"%edi", "%edx");
       __asm__("addl %0, %%esp\n"::"m"(argSize)); /* if not stdcall, do this.
    //   Beacause, the stdcall will clean up the stack itself.
    //             the cdecl will not. So we have to clean the stack after cdecl call.*/
}
#elif __WORDSIZE == 64
//! x86_64 arguments :rdi, rsi, rdx, rcx, r8, r9
inline void call_stdfunc(void* func, int argSize, void* arg)
{
    switch(argSize >> 3){
        case 0:
            __asm__(
                    "call *%%rax\n"
                    :
                    :"a"(func), "b"(arg));
            break;
        case 1:
            __asm__(
                    "movq (%%rbx), %%rdi\n"
                    "call *%%rax\n"
                    :
                    :"a"(func), "b"(arg));
            break;
        case 2:
            __asm__(
                    "movq (%%rbx), %%rdi\n"
                    "movq 8(%%rbx), %%rsi\n"
                    "call *%%rax\n"
                    :
                    :"a"(func), "b"(arg));
            break;
        case 3:
            __asm__(
                    "movq (%%rbx), %%rdi\n"
                    "movq 8(%%rbx), %%rsi\n"
                    "movq 16(%%rbx), %%rdx\n"
                    "call *%%rax\n"
                    :
                    :"a"(func), "b"(arg));
            break;
        case 4:
            __asm__(
                    "movq (%%rbx), %%rdi\n"
                    "movq 8(%%rbx), %%rsi\n"
                    "movq 16(%%rbx), %%rdx\n"
                    "movq 24(%%rbx), %%rcx\n"
                    "call *%%rax\n"
                    :
                    :"a"(func), "b"(arg));
            break;
        case 5:
            __asm__(
                    "movq (%%rbx), %%rdi\n"
                    "movq 8(%%rbx), %%rsi\n"
                    "movq 16(%%rbx), %%rdx\n"
                    "movq 24(%%rbx), %%rcx\n"
                    "movq 32(%%rbx), %%r8\n"
                    "call *%%rax\n"
                    :
                    :"a"(func), "b"(arg));
            break;
        case 6:
            __asm__(
                    "movq (%%rbx), %%rdi\n"
                    "movq 8(%%rbx), %%rsi\n"
                    "movq 16(%%rbx), %%rdx\n"
                    "movq 24(%%rbx), %%rcx\n"
                    "movq 32(%%rbx), %%r8\n"
                    "movq 40(%%rbx), %%r9\n"
                    "call *%%rax\n"
                    :
                    :"a"(func), "b"(arg));
            break;
        default:
            __asm__ __volatile__ (
                    "subq %%rcx, %%rsp\n"
                    "movq %%rsp, %%rdi\n"
                    "rep movsb\n"
                    "movq %%rsp, %%rbx\n"
                    "movq (%%rbx), %%rdi\n"
                    "movq 8(%%rbx), %%rsi\n"
                    "movq 16(%%rbx), %%rdx\n"
                    "movq 24(%%rbx), %%rcx\n"
                    "movq 32(%%rbx), %%r8\n"
                    "movq 40(%%rbx), %%r9\n"
                    "call *%%rax\n"
                    :
                    :"a"(func),"c"(argSize - 6 * sizeof(long)), "S"(arg)
                    :"%rdi", "%rdx");
            break;
    }
}

inline void call_cdeclfunc(void* func, int argSize, void* arg)
{
    call_stdfunc(func,argSize,arg);
}
#endif
#else      /* -----  not _PTHREAD  ----- */
#define typeof(x) x
#define push2stack(v){ switch(_INTSIZEOF(typeof(v))) {\
case 1: *(char*)(pcur) = v; break; \
case 2: *(short*)(pcur) = v; break; \
case 4: *(int*)(pcur) = v; break; \
case 8: *(long long*)(pcur) = v; break; \
}\
pcur += _INTSIZEOF(typeof(v));\
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  call_stdfunc
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  call_stdfunc
 * =====================================================================================
 */
inline void call_stdfunc(void* func, int argSize, void* arg)
	funcInfo_t* ft = (funcInfo_t*)p;
	unsigned int f = (unsigned int)func;
	unsigned int argSize = (unsigned int)argSize;
	unsigned int stack = (unsigned int)arg;
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
    //   __asm add esp,argSize/* if not stdcall, do this*/
}

inline void call_cdeclfunc(void* func, int argSize, void* arg)
	funcInfo_t* ft = (funcInfo_t*)p;
	unsigned int f = (unsigned int)func;
	unsigned int argSize = (unsigned int)argSize;
	unsigned int stack = (unsigned int)arg;
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
       __asm add esp,argSize/* if not stdcall, do this*/
}

#endif     /* -----  not _PTHREAD  ----- */

inline void call_func(void* func, int argSize, void* arg)
{
#ifdef DEFAULT_STDCALL
    call_stdfunc(func, argSize, arg);
#else
    call_cdeclfunc(func, argSize, arg);
#endif
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  thread_func_g
 *  Description:  the thread template for launching simple function,
 *                it copy the arguments from p->esp to the stack, then call the p->f;
 *  	  Input:  
 *       Output:
 *      Example:  thread_func_g
 * =====================================================================================
 */
static __thread_ret thread_func_g(void* p){
    funcInfo_t* ft = (funcInfo_t*)p;
    if(p == NULL) return NULL;
    call_func(ft->f,ft->argSize,ft->esp);
    /* 
     * judge if the p is on the heap
    if((size_t)p < (size_t)&ft){// p is on the heap 
        //printf("heap\n");
        //free(p); //! error with O2/3, 
    }
    */
    if(((task_t*)p)->flag == mem_heap){
        printf("");
        free(p);
    }
    return NULL;
}

#define slaunchTemplateThread()      create_thread(thread_func_g, global_funcInfo)// /*thread_func_g(&global_funcInfo);*/
#define slaunchTemplateThreadStack() create_thread(thread_func_g, &global_funcInfo)// /*thread_func_g(&global_funcInfo);*/
	
#define slauncher_header(sfunc, argnum)  ({ funcInfo_t* global_funcInfo= create_task();\
        (({global_funcInfo->f = (void*) sfunc; slaunchArg ## argnum
#define slaunchArg_part0 {char* pcur= global_funcInfo->esp; 
#define slaunchArg_part2  global_funcInfo->argSize = pcur - global_funcInfo->esp;\
}}),\
slaunchTemplateThread()); });

///////////////////// 0 args ////////////////////////////////////////////
#define slaunchArg0( ) slaunchArg_part0 slaunchArg_part2
#define slaunch0(sfunc) slauncher_header(sfunc,0) 

///////////////////// 1 args ////////////////////////////////////////////
#define slaunchArg1( a00) {char* pcur= global_funcInfo->esp; \
	push2stack(a00);\
	global_funcInfo->argSize = pcur - global_funcInfo->esp;\
}}),\
slaunchTemplateThread()); });

#define slaunch1(sfunc) ({ funcInfo_t* global_funcInfo= create_task();\
        (({global_funcInfo->f = (void*) sfunc; slaunchArg1

///////////////////// 2 args ////////////////////////////////////////////
#define slaunchArg2( a00, a01) {char* pcur= global_funcInfo->esp; \
	push2stack(a00); \
	push2stack(a01); \
	global_funcInfo->argSize = pcur - global_funcInfo->esp;\
}}),\
slaunchTemplateThread()); });

#define slaunch2(sfunc) ({ funcInfo_t* global_funcInfo= create_task();\
        (({global_funcInfo->f = (void*) sfunc; slaunchArg2

///////////////////// 3 args ///////////////////////////////////////////
#if 0
#define slaunchArg3( a00, a01, a02) {char* pcur= global_funcInfo.esp; \
	push2stack(a00); \
	push2stack(a01); \
	push2stack(a02); \
	global_funcInfo.argSize = pcur - global_funcInfo.esp;\
};\
slaunchTemplateThread();

#define slaunch3(sfunc) global_funcInfo.flag=mem_stack; global_funcInfo.f = (void*) sfunc; slaunchArg0  
#endif	

#define slaunchArg3(a00,a01,a02) slaunchArg_part0 pushArgtoStack3(a00,a01,a02) slaunchArg_part2
#define slaunch3(sfunc) slauncher_header(sfunc,3) 
///////////////////// 4 args ///////////////////////////////////////////
#define slaunchArg4(a00,a01,a02,a03) slaunchArg_part0 pushArgtoStack4(a00,a01,a02,a03) slaunchArg_part2
#define slaunch4(sfunc) slauncher_header(sfunc,4) 
/******************************************************************************
 *                                                                            *
 ***************************** launch task to an idle thread (dlaunch) ********
 * Function: find an idle thread and disptch task to the thread               *
 ******************************************************************************/
#define GID_MASK 0xffff0000
#define TID_MASK 0x0000ffff
#define dlaunchTemplateThread() launch_task(global_funcInfo)

#define dlauncher_header(sfunc, argnum)  ({ funcInfo_t* global_funcInfo= create_task();\
        (({global_funcInfo->f = (void*) sfunc; dlaunchArg ## argnum
#define dlaunchArg_part0 {char* pcur= global_funcInfo->esp; 
#define dlaunchArg_part2  global_funcInfo->argSize = pcur - global_funcInfo->esp;\
}}),\
dlaunchTemplateThread()); });

inline void appandTask(task_t* task, int gid, int tid);
int getIdleThreadDefault();
inline int launch_task(funcInfo_t* task)
{
    int gtid = getIdleThreadDefault();
    int gid = GID(gtid);
    if (gtid ==-1 ){// None idle thread exists.
        call_func(task->f, task->argSize, task->esp);
    }else{
        appandTask(task, gid,gtid&TID_MASK);        
    }
    if(task->flag == mem_heap)
        free(task);
    return gtid;
}
///////////////////// 0 args ////////////////////////////////////////////
#define dlaunchArg0( ) dlaunchArg_part0 dlaunchArg_part2
#define dlaunch0(sfunc) dlauncher_header(sfunc,0) 
///////////////////// 1 args ////////////////////////////////////////////
#define dlaunchArg1(a00 ) dlaunchArg_part0 pushArgtoStack1(a00) dlaunchArg_part2
#define dlaunch1(sfunc) dlauncher_header(sfunc,1) 
///////////////////// 2 args ///////////////////////////////////////////
#define dlaunchArg2( a00, a01) {char* pcur= global_funcInfo->esp; \
    push2stack(a00); \
    push2stack(a01); \
    global_funcInfo->argSize = pcur - global_funcInfo->esp;\
}}),\
dlaunchTemplateThread()); });

#define dlaunch2(sfunc)  ({ funcInfo_t* global_funcInfo= create_task();\
        (({global_funcInfo->f = (void*) sfunc; dlaunchArg2

///////////////////// 3 args ///////////////////////////////////////////
#define dlaunchArg3(a00,a01,a02 ) dlaunchArg_part0 pushArgtoStack3(a00,a01,a02) dlaunchArg_part2
#define dlaunch3(sfunc) dlauncher_header(sfunc,3) 
///////////////////// 4 args ///////////////////////////////////////////
#define dlaunchArg4(a00,a01,a02,a03 ) dlaunchArg_part0 pushArgtoStack4(a00,a01,a02,a03) dlaunchArg_part2
#define dlaunch4(sfunc) dlauncher_header(sfunc,4) 
/***************************************************************************************
 *
 *the Launcher end
 *
 **************************************************************************************/

#endif   /* ----- #ifndef THREADLAUNCHER_HEADER__INC  ----- */
