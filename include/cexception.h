/*
 * =====================================================================================
 *       Filename:  
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/17/2010 08:34:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai , djx.zhenghua@gmail.com
 *
 * =====================================================================================
 */
/***************************************************************************************
 * Reference: C interface and implementation
 * The class/struct name is Capital first.
 * The variable name is 
 ***************************************************************************************/

#ifndef  CEXCEPTION__INC
#define  CEXCEPTION__INC

#include <setjmp.h>
#if defined(_MSC_VER)
#       define THREAD_LOCAL __declspec(thread)
#elif defined(__GNUC__)
#       define THREAD_LOCAL __thread
#endif

#if  defined(_MSC_VER)
typedef unsigned long TlsKey;
#       define TLS_CREATE(x)        x = tlsAlloc()
#       define TLS_GET_VALUE(x)     tlsGetValue(x)
#       define TLS_SET_VALUE(x, v)  tlsSetValue(x, v)
#       define TLS_DELETE(x)        tlsFree(x)
#elif defined(__GNUC__)
#include <pthread.h>
typedef pthread_key_t TlsKey;
#       define TLS_CREATE(x)        if (0 != pthread_key_create(&(x), NULL))  x = NULL
#       define TLS_GET_VALUE(x)     pthread_getspecific(x)
#       define TLS_SET_VALUE(x, v)  pthread_setspecific(x, v)
#       define TLS_DELETE(x)        pthread_key_delete(x)
#endif

#define EXCEPTION_TYPE(x) ExeptionType_ ##x

enum{
    ExceptionType_try=0, 
    EXCEPTION_TYPE(int) = 1, 
    EXCEPTION_TYPE(char) = 2, 
};
typedef unsigned long long U64;
typedef struct ExceptionFrame_t{
    struct ExceptionFrame_t * prev;
    jmp_buf env;
    U64 value;
} ExceptionFrame_t;

#ifndef  __cplusplus
/*****************************************************************************
 *                         C                                                 *
 * **************************************************************************/
#define try do{                           \
    volatile int ceh_type;                \
    ExceptionFrame_t cur_ceh_frame;       \
    cur_ceh_frame.prev = ceh_stack;       \
    ceh_stack = &cur_ceh_frame;           \
    ceh_type=setjmp(cur_ceh_frame.env);  \
    if(ceh_type == 0){

#define CATCH(type, ceh) \
        if(ceh_type == 0) ceh_stack = ceh_stack->prev;\
    }else if(ceh_type == EXCEPTION_TYPE(type)){\
        type ceh = *(type*)&(ceh_stack->value);\
        ceh_stack = ceh_stack->prev;

#define CATCHALL(...) \
        if(ceh_type == 0) ceh_stack = ceh_stack->prev;\
    }else {\
        ceh_stack = ceh_stack->prev;


#define endtry }\
}while(0);

#define Throw(type, x) {*(type*)&(ceh_stack->value) = x; longjmp(ceh_stack->env, EXCEPTION_TYPE(type));}    

//THREAD_LOCAL    ExceptionFrame_t* ceh_stack;
#else      /* -----  __CPLUSPLUS  ----- */
/*****************************************************************************
 *                         C++                                                 *
 * **************************************************************************/
#include <exception>
#include <iostream>
#define Throw(type, x) throw x;
#define CATCH(type, x) catch(type x) 
#define CATCHALL catch
#define endtry
#endif     /* -----  not __CPLUSPLUS  ----- */

#endif   /* ----- #ifndef CEXCEPTION__INC  ----- */
