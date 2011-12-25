// cothread.c
#include<assert.h> 
#include<stdlib.h> 
#include<setjmp.h> 
#include"dmthread.h" 
#include <stdio.h>

void remove_thread();

void cp_ucontext2sigcontext(sigcontext* dst, ucontext_t* src);

volatile unsigned int Inschedule= 0;
sched_system sys={0};


void cp_sigcontext2ucontext( ucontext_t* dst, sigcontext* src)
{
    __asm__("rep movsb\n"
            :
            :"c"(sizeof(
                    //gregset_t
                    mcontext_t
                    )), "S"(src), "D"(&(dst->uc_mcontext))
           );
}


void save_frame(sigcontext* frame, dmthread_t *thread)
{
    size_t *psrc = (size_t*) frame;
    size_t *pdst = (size_t*) &(thread->sig_context);
    unsigned int i; 
    thread->rframe_type = (unsigned int)FRAME_SIGCONTEXT;
#if 0
    for(i = 0; i< sizeof(sigcontext) / sizeof(size_t); i++){
        pdst[i] = psrc[i];
    }
#else
    __asm__(
            "rep movsb\n"
            :
            :"c"(sizeof(sigcontext)), "S"(psrc), "D"(pdst)
           );
#endif
}

void recover_frame(sigcontext* frame, dmthread_t *thread)
{
    size_t *pdst = (size_t*) frame;
    size_t *psrc = (size_t*) &(thread->sig_context);
    unsigned int i; 
#if 0
    for(i = 0; i< sizeof(sigcontext) / sizeof(size_t); i++){
        pdst[i] = psrc[i];
    }
#else
    if(thread->rframe_type == FRAME_UCONTEXT){
        cp_ucontext2sigcontext(&(thread->sig_context),&(thread->u_context) );
    }
    __asm__(
            "rep movsb\n"
            :
            :"c"(sizeof(sigcontext)), "S"(psrc), "D"(pdst)
           );
#endif
}

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
        sys.current  =  sys.threads;
    } else  {
        sys.unfreed_stack  =  sys.current -> thread.stack;
        thread_list *prev =_remove_thread(sys.current);
        sys.current = getNext(prev);
    }

    if  (sys.current  ==   0 ) {
        sys.current  =  sys.threads;
        assert(0);
    }
}


void switchto(sigcontext* psig_context)
{
    if(sys.current)
        recover_frame(psig_context, &(sys.current->thread));
}

void requir_schedule()
{
    //raise(SIGALRM);
    if(1){
        thread_list* next = sys.current->next;
        if(next->thread.status_w == STATUS_CREATED)
        {
            myprintf("raise");
            raise(SIGALRM);
            return;
        }
    }
    myprintf("requir_schedule\n");
    thread_list *  old;
    Inschedule = 1;
    if(sys.current->thread.status == STATUS_DEAD){
        myprintf("remove\n");
        remove_thread();
        if(sys.current->thread.rframe_type == FRAME_SIGCONTEXT){
            cp_sigcontext2ucontext(&(sys.current->thread.u_context), &(sys.current->thread.sig_context));
        }
        Inschedule = 0;
        myprintf("setcontext\n");
       // setcontext(&(sys.current->thread.u_context));
        swapcontext((sys.unfreed_stack), &(sys.current->thread.u_context));
        return ;
    }
    free_unfree_stack();
    old  =  sys.current;
    if(sys.current == 0){
        assert(0);
    }else{
        sys.current  =  sys.current -> next ;
        if  (!sys.current){
            sys.current  =  sys.threads;
        }

        if(sys.current){
            if(sys.current->thread.rframe_type == FRAME_SIGCONTEXT){
                cp_sigcontext2ucontext(&(sys.current->thread.u_context), &(sys.current->thread.sig_context));
            }
            old->thread.rframe_type = (unsigned int)FRAME_UCONTEXT;
            myprintf("swap %d\n", sys.current);
            myprintf("swap2 %d\n", sys.current);
            Inschedule = 0;
            swapcontext(&(old->thread.u_context), &(sys.current->thread.u_context));
        }
    }
}

void start_thread(thread_list *  iter)
{
    char *  stack_btm;
    ptr_size* gsp;
    ptr_size* gbp;
    int i;
    int disp;
    //! copy stack frame
    iter->thread.stack =(char * )malloc(STACK_SIZE  +  RESERVED_STACK);
    __asm( "mov %%" bp_register ",%0":"=m"(gbp):);
    __asm( "mov %%" sp_register ",%0":"=m"(gsp):);
    disp = (char*)gbp - (char*)gsp;
    if(disp > 256) 
        disp =((int) ( ((char*) &stack_btm) - ((char*) &disp) )) + sizeof(ptr_size); 
    myprintf("disp :%d\n", disp);
    stack_btm  =  iter -> thread.stack  +  STACK_SIZE - disp - (4)*sizeof(ptr_size);
    for(i =0;i<disp /sizeof(ptr_size)+ 4;i++){
        ((ptr_size*)stack_btm)[i] = gsp[i];
    }
    gbp = (ptr_size*)((char*)stack_btm + disp);
    //!CHANGE_STACK(stack_btm);
    __asm( "mov %0, %%" sp_register ::"m"(stack_btm));
    __asm( "mov %0, %%" bp_register ::"m"(gbp));

    raise(SIGUSR1);
    if  (iter->thread.status_w){
        sys.current->thread.status_w = STATUS_IN_THREAD;
#if 1
        {
            getcontext(&(iter->thread.u_context));
            myprintf("get fp:%x\n", iter->thread.u_context.uc_mcontext.fpregs);
            //iter->thread.u_context.uc_stack.ss_sp=iter->thread.stack ;
            //iter->thread.u_context.uc_stack.ss_size= STACK_SIZE;
            //iter->thread.u_context.uc_stack.ss_flags= 0;
            //makecontext(&(iter->thread.u_context), iter->thread.kernel, iter->thread.arg); 
        }
#endif
        (iter -> thread.kernel)(iter -> thread.arg);

        if  (sys.threads -> next ){
            sys.current->thread.status=STATUS_DEAD;
            //requir_schedule();
            raise(SIGALRM);
        }else {
            assert(0);
        }
    }else{
        //getcontext(&(iter->thread.u_context));
        iter->thread.rframe_type = (unsigned int)FRAME_SIGCONTEXT;
        iter->thread.status_w = STATUS_CREATED;
    }
}


