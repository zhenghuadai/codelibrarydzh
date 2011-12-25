
#ifndef  DMTHREAD_HEADER
#define  DMTHREAD_HEADER
#include <signal.h>
#include <sys/time.h>
#include <sys/ucontext.h>
# if __WORDSIZE == 64
#define bp_register "rbp"
#define sp_register "rsp"
#define OFFSET_TO_SIGCONTEXT 7 
# else
#define bp_register "ebp"
#define sp_register "esp"
#define OFFSET_TO_SIGCONTEXT 3 
# endif
#if defined(__GNUC__)
#define CHANGE_STACK(newaddr) __asm( "mov %0, %%rsp"::"m"(newaddr));
#else
#define CHANGE_STACK(newaddr) _asm mov esp, newaddr
#endif

#define STACK_SIZE  65536 
#define RESERVED_STACK  4 



typedef void ( * thread_func_t)(void * );

typedef struct sigcontext sigcontext;
typedef unsigned long long ptr_size ;

enum{FRAME_JMPBUF=1, FRAME_SIGCONTEXT=0, FRAME_TWO=2, FRAME_UCONTEXT=3};
enum{STATUS_DEAD=1, STATUS_READY=2};
enum{STATUS_IN_MAIN=0, STATUS_CREATED=1, STATUS_IN_THREAD=2 };

typedef struct dmthread_t
{
#if 1
    ucontext_t u_context;
    sigcontext sig_context;
#else
    union{
        ucontext_t u_context;
        struct{
            unsigned long int uc_flags;
            struct ucontext *uc_link;
            stack_t uc_stack;
            sigcontext sig_context;
            __sigset_t uc_sigmask;
            struct _libc_fpstate __fpregs_mem;
        };
    };
#endif
    unsigned int rframe_type;
    unsigned short status;
    unsigned short priority;
    thread_func_t kernel;
    void *  arg;
    char *  stack;
    volatile unsigned int status_w;
} dmthread_t;


typedef struct thread_list
{
    dmthread_t thread;
    volatile struct thread_list *   next ;
    struct thread_list *   prev;
} thread_list;

typedef struct sched_system
{
    thread_list *  threads;
    thread_list *  current;
    int  main_esp, main_ebp;
    char  * unfreed_stack;
    int  retaddr;
} sched_system;


extern sched_system sys;

void reg_thread(thread_func_t f, void *  arg);

int setTimer ();
void siguser1_handler(int signo);

static thread_list*_new_thread(thread_func_t f, void *  arg)
{
    thread_list *  new_thread;
    new_thread  =  (thread_list * )malloc(sizeof(thread_list));
    new_thread -> thread.arg  =  arg;
    new_thread -> thread.stack  =   0 ;
    new_thread -> thread.kernel=  f;
    new_thread -> thread.status=  0;
    new_thread -> thread.priority=  0;
    new_thread -> thread.status_w = STATUS_IN_MAIN;
    new_thread -> next = new_thread;
    new_thread -> prev = new_thread;
    return new_thread;
}

static inline thread_list* getNext(thread_list* cur)
{
   if( cur -> next -> next -> thread.priority < cur -> next -> thread.priority )
       return cur->next->next;
   else 
       return cur->next;
}

static inline void _insert_thread(thread_list* newt, thread_list* prev)
{
    newt->next = prev->next;
    newt->prev = prev;
    newt->next->prev= newt;
    prev->next = newt;
}

//! return Previous( t->prev)
static inline thread_list* _remove_thread(thread_list* t)
{
    thread_list *  iter = t -> prev;

    assert (iter  &&  iter -> next   ==  t);
    iter -> next   =  t -> next ;
    t -> next -> prev = iter;
    free(t);
    return iter;
}

#if 1
#define myprintf(...) fprintf(stdout, __VA_ARGS__); fflush(stdout);
#else
#define myprintf(...)
#endif
#endif     /* -----  not DMTHREAD_HEADER  ----- */
