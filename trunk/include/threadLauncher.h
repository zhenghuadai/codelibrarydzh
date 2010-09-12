
#ifndef  THREADLAUNCHER_HEADER__INC
#define  THREADLAUNCHER_HEADER__INC
#include "stdio.h"
#include "stdlib.h"
#if defined(_MSC_VER)
#       define THREAD_LOCAL __declspec(thread)
#elif defined(__GNUC__)
#       define THREAD_LOCAL __thread
#endif
/************************************************************************************
 *
 *the Launcher
 *
 ***********************************************************************************/
///////////////// public ////////////////////////////////////////
#define fArgTypename(f) f##Arg_t

#define AAAint(x) int
#define BBBint(x) x 
#define AAApu8(x) pu8
#define BBBpu8(x) x 
#define AAApu32(x) pu32
#define BBBpu32(x) x 


#define AAA(a) AAA##a
#define BBB(a) BBB##a  // BBB(int(a))
#define launchfunc( pfuncKernel, argNum) c[tid].func = pfuncKernel; {\
        char* pcur=(char*)c[tid].kArg;  c[tid].arg= (void*)pcur; pushtArg##argNum

//////////////////// 0 args ////////////////////////////////////////////////////
#define pushtArg0()\
}\
}

#define launchfunc0( pfuncKernel) c[tid].func = pfuncKernel; {\
	char* pcur=(char*)c[tid].kArg;  c[tid].arg= (void*)pcur; pushtArg0 
#define launch0(tid0) { int tid = tid0; launchfunc0  
	
//////////////////// 2 args ////////////////////////////////////////////////////
#define pushtArg2(a00,a01)\
	push2stack(a00); \
	push2stack(a01); \
	c[tid].argSize = pcur - (char*) c[tid].arg;\
}\
}

#define launchfunc2( pfuncKernel) c[tid].func = pfuncKernel; {\
	char* pcur=(char*)c[tid].kArg;  c[tid].arg= (void*)pcur; pushtArg2 
#define launch2(tid0) { int tid = tid0; launchfunc2  
	
//////////////////// 3 args ////////////////////////////////////////////////////
#define pushtArg3(a00,a01,a02)\
	push2stack(a00); \
	push2stack(a01); \
	push2stack(a02); \
	c[tid].argSize = pcur - (char*) c[tid].arg;\
}\
}

#define launchfunc3( pfuncKernel) launchfunc( pfuncKernel, 3)
#define launch3(tid0) { int tid = tid0; launchfunc3  
	
//////////////////// 5 args ////////////////////////////////////////////
/////////////////// 6 args ////////////////////////////////////////////////////
#define pushtArg6(a00,a01,a02,a03,a04,a05)\
	push2stack(a00); \
	push2stack(a01); \
	push2stack(a02); \
	push2stack(a03); \
	push2stack(a04); \
	push2stack(a05); \
	c[tid].argSize = pcur - (char*) c[tid].arg;\
}\
}

#define launchfunc6( pfuncKernel) launchfunc( pfuncKernel, 6)
#define launch6(tid0) { int tid = tid0; launchfunc6  

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
#define launch16(tid0) { int tid = tid0; launchfunc16  
/*******************************************************************************************************************
 *                                                                                                                 *
 ***************************** launch a single function ************************************************************
 *                                                                                                                 *
 *******************************************************************************************************************/
typedef struct{
	void* f;
	int argSize;
	char esp[128];
}funcInfo_t;
static THREAD_LOCAL funcInfo_t global_funcInfo;

#ifdef _PTHREAD
#define push2stack(v) {(*(typeof(v)*)pcur)=v; pcur += _INTSIZEOF(typeof(v));}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  call_stdfunc
 *  Description:
 *  	  Input:  
 *       Output:
 *      Example:  call_stdfunc
 * =====================================================================================
 */
inline void call_stdfunc(void* func, void* arg, int argSize)
{
    __asm__(
            "subl %%ecx, %%esp\n"
            "movl %%esp, %%edi\n"
            "rep movsb\n"
            "call *%%eax\n"
            :
            :"a"(func),"c"(argSize), "S"(arg)
            :"%edi");
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
    //   __asm__("addl %0, %%esp\n"::"r"(ft->argSize)); /* if not stdcall, do this*/
    if((size_t)p < (size_t)&ft){// p is on the heap 
//        printf("heap\n");
//        free(p); //! error with O2/3, 
    }
}


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
 *         Name:  thread_func_g
 *  Description:  the thread template for launching simple function,
 *                it copy the arguments from p->esp to the stack, then call the p->f;
 *  	  Input:  
 *       Output:
 *      Example:  thread_func_g
 * =====================================================================================
 */
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
#endif     /* -----  not _PTHREAD  ----- */

#define launchTemplateThread() \
create_thread(thread_func_g, global_funcInfo)// /*thread_func_g(&global_funcInfo);*/
	
#define launchTemplateThreadStack() \
create_thread(thread_func_g, &global_funcInfo)// /*thread_func_g(&global_funcInfo);*/
	
///////////////////// 0 args ////////////////////////////////////////////
#define slaunchArg0( ) {char* pcur= global_funcInfo.esp; \
	global_funcInfo.argSize =0;\
}\
launchTemplateThread();

#define slaunch0(sfunc) global_funcInfo.f = (void*) sfunc; slaunchArg0

///////////////////// 1 args ////////////////////////////////////////////
#define slaunchArg1( a00) {char* pcur= global_funcInfo->esp; \
	push2stack(a00);\
	global_funcInfo->argSize = pcur - global_funcInfo->esp;\
}}),\
launchTemplateThread()); });

#define slaunch1(sfunc) ({ funcInfo_t* global_funcInfo= (funcInfo_t*)malloc(sizeof(funcInfo_t));\
        (({global_funcInfo->f = (void*) sfunc; slaunchArg1

///////////////////// 2 args ////////////////////////////////////////////
#define slaunchArg2( a00, a01) {char* pcur= global_funcInfo->esp; \
	push2stack(a00); \
	push2stack(a01); \
	global_funcInfo->argSize = pcur - global_funcInfo->esp;\
}}),\
launchTemplateThread()); });

#define slaunch2(sfunc) ({ funcInfo_t* global_funcInfo= (funcInfo_t*)malloc(sizeof(funcInfo_t));\
        (({global_funcInfo->f = (void*) sfunc; slaunchArg2

///////////////////// 3 args ///////////////////////////////////////////

#define slaunchArg3( a00, a01, a02) {char* pcur= global_funcInfo.esp; \
	push2stack(a00); \
	push2stack(a01); \
	push2stack(a02); \
	global_funcInfo.argSize = pcur - global_funcInfo.esp;\
};\
launchTemplateThreadStack();

#define slaunch3(sfunc) global_funcInfo.f = (void*) sfunc; slaunchArg3
	
/***************************************************************************************
 *
 *the Launcher end
 *
 **************************************************************************************/

#endif   /* ----- #ifndef THREADLAUNCHER_HEADER__INC  ----- */
