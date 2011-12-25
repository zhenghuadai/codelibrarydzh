#include <sys/time.h>
#include <signal.h>
#include<assert.h> 
#include  "dmthread.h" 
extern sched_system sys;
void start_thread(thread_list *  iter);
void initSignal();
extern volatile unsigned int Inschedule;
void schedule(sigcontext*);


void reg_thread(thread_func_t f, void *  arg)
{
    thread_list *  new_thread;
    static int hasInitialized = 0;
    if(  hasInitialized == 0){
        initSignal();
        hasInitialized = 1; 
    }
    new_thread = _new_thread(f, arg);
    if(sys.threads == 0){
        thread_list *  main_thread = _new_thread(0,0);
        sys.threads = sys.current = main_thread;
    }
    _insert_thread(new_thread, sys.threads->prev);
    sys.current = new_thread;
    start_thread( new_thread);
    sys.current = sys.threads;
}

void timeHandler (int signo)
{
    unsigned int i, j;
    sigcontext* psig_context;    
    //__asm("push %%rbp;"  "movq %%rsp, %%rbp"::);
    if(signo != SIGALRM) return ;
    if(Inschedule) return;
    printf( " Schedule\n " ); 
    signal(SIGALRM,timeHandler);
    __asm( "lea (%%" bp_register ", %1), %0":"=r"(psig_context): "r"(OFFSET_TO_SIGCONTEXT* sizeof(ptr_size*)));
    printf("fp:%0x\n", psig_context->fpstate);
    schedule(psig_context);
    //__asm("leave");
}
 
void siguser1_handler(int signo)
{
    sigcontext* psig_context;    
    __asm( "lea (%%" bp_register ", %1), %0":"=r"(psig_context): "r"(OFFSET_TO_SIGCONTEXT* sizeof(ptr_size*)));
    save_frame(psig_context, &(sys.current->thread));
    signal(SIGUSR1, siguser1_handler);
}


void schedule(sigcontext* psig_context)
{
    thread_list *  old;
    if(sys.current->thread.status == STATUS_DEAD){
        remove_thread();
        switchto(psig_context);
        return ;
    }
    free_unfree_stack();
    old  =  sys.current;
    if(sys.current == 0){
        assert(0);
    }else{
        //sys.current  =  sys.current -> next ;
        sys.current = getNext(sys.current);
        if  (!sys.current){
            sys.current  =  sys.threads;
            assert(0);
        }

        if(sys.current){
            save_frame(psig_context, &(old->thread));
            old->thread.rframe_type = FRAME_SIGCONTEXT;

            recover_frame(psig_context, &(sys.current->thread));
        }
    }
}


void cp_ucontext2sigcontext(sigcontext* dst, ucontext_t* src)
{
#define SIGCONTEXT_SAVE( sig, x) long x = *(long*) &(sig -> x)
#define SIGCONTEXT_RESTORE( sig, x)  *(long*) &(sig -> x) = x;
    //printf(" u 2 sig\n");
    //fflush(stdout);
    struct _fpstate * oldfp = dst->fpstate;
# if __WORDSIZE == 64
    long cs = *(long*)&(dst-> cs);
#else
    SIGCONTEXT_SAVE(dst, gs);
    SIGCONTEXT_SAVE(dst, fs);
    SIGCONTEXT_SAVE(dst, es);
    SIGCONTEXT_SAVE(dst, ds);
    SIGCONTEXT_SAVE(dst, cs);
    SIGCONTEXT_SAVE(dst, ss);
#endif
    __asm__("rep movsb\n"
            :
            :"c"(sizeof(
                    //gregset_t 
                    mcontext_t
                    )), "S"(&(src->uc_mcontext)), "D"(dst)
           );
    dst->fpstate = 0; //! must copy from user to kernel
# if __WORDSIZE == 64
    *(long*)&(dst-> cs) = cs;
#else
    SIGCONTEXT_RESTORE(dst, gs);
    SIGCONTEXT_RESTORE(dst, fs);
    SIGCONTEXT_RESTORE(dst, es);
    SIGCONTEXT_RESTORE(dst, ds);
    SIGCONTEXT_RESTORE(dst, cs);
    SIGCONTEXT_RESTORE(dst, ss);
#endif
}
