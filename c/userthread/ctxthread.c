// cothread.c
#include<assert.h> 
#include<stdlib.h> 
#include<setjmp.h> 
#include"dmthread.h" 
#include <stdio.h>
#define STACK_SIZE 4096

void remove_thread();

volatile unsigned int Inschedule= 0;
sched_system sys={0};

void free_unfree_stack()
{
    if  (sys.unfreed_stack){
        free(sys.unfreed_stack);
        sys.unfreed_stack  =   0 ;
    }
}

void remove_thread()
{
    free_unfree_stack();
    if  (sys.current  ==  sys.threads) {
        sys.unfreed_stack  =  sys.current -> thread.stack;
        sys.threads  =  getNext(sys.current);
        thread_list *prev =_remove_thread(sys.current);
        prev->thread.u_context.uc_link =& prev->next->thread.u_context;
        sys.current  =  sys.threads;
    } else  {
        sys.unfreed_stack  =  sys.current -> thread.stack;
        thread_list *prev =_remove_thread(sys.current);
        prev->thread.u_context.uc_link =& prev->next->thread.u_context;
        sys.current = getNext(prev);
    }

    if  (sys.current  ==   0 ) {
        sys.current  =  sys.threads;
        assert(0);
    }
}


void switchto(ucontext_t* u_context)
{
    if(sys.current)
        setcontext(&(sys.current->thread.u_context));
}

void start_thread(thread_list *  iter)
{
    sys.current->thread.status_w = STATUS_IN_THREAD;
    (iter -> thread.kernel)(iter -> thread.arg);

    if  (sys.threads -> next ){
        sys.current->thread.status=STATUS_DEAD;
        schedule();
    }else {
        assert(0);
    }
}


void reg_thread(thread_func_t f, void *  arg)
{
    thread_list *  new_thread;
    ucontext_t* fcontext;
    static int hasInitialized = 0;
    if(  hasInitialized == 0){
        hasInitialized = 1; 
    }
    new_thread = _new_thread(f, arg);
    if(sys.threads == 0){
        thread_list *  main_thread = _new_thread(0,0);
        sys.threads = sys.current = main_thread;
    }
    _insert_thread(new_thread, sys.threads->prev);

    fcontext = & new_thread->thread.u_context;
    getcontext(fcontext);
    if ((fcontext->uc_stack.ss_sp = (char *) malloc(STACK_SIZE)) != NULL) {
        fcontext->uc_stack.ss_size = STACK_SIZE;
        fcontext->uc_stack.ss_flags = 0;
        fcontext->uc_link = &(new_thread->next->thread.u_context);
        //makecontext(fcontext,f,1,arg);
        makecontext(fcontext,start_thread,1,new_thread);
        printf("fp:%x\n", fcontext->uc_mcontext.fpregs);
    }
    else {
        perror("not enough storage for stack");
        abort();
    }

    sys.current = sys.threads;
}

void schedule()
{
    thread_list *  old;
    if(sys.current->thread.status == STATUS_DEAD){
        remove_thread();
        sys.current = getNext(sys.current->prev);
        switchto(&sys.current->thread.u_context);
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
            swapcontext(& old->thread.u_context, & sys.current->thread.u_context);
        }
    }
}


void dmthread_join()
{
    while(sys.current->next && (sys.current->next != sys.current)){
        myprintf("This is main ...\n");
        //requir_schedule();
        sys.current->thread.priority = 1;
        schedule();
        printf("%lx && (%lx != %lx)\n",sys.current->next ,sys.current->next , sys.current);
    }
}

