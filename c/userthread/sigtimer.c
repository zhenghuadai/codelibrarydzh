#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include  "dmthread.h" 
#include <math.h>
#if 1
#define myprintf(...) printf(__VA_ARGS__)
#else
#define myprintf(...)
#endif
void siguser1_handler(int signo);

extern sched_system sys;
void save_frame(sigcontext* frame, dmthread_t *thread);

void timeHandler (int signo);

int setTimer ()
{
    struct itimerval value2,ovalue;

    signal(SIGALRM,timeHandler);
    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 100000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 10000;
    setitimer(ITIMER_REAL, &value2, &ovalue);
}


void dmthread_join()
{
    while(sys.current->next && (sys.current->next != sys.current)){
        myprintf("This is main ...\n");
        //requir_schedule();
        sys.current->thread.priority = 1;
        raise(SIGALRM);
    }
}

void initSignal()
{
    signal(SIGUSR1, siguser1_handler);
    setTimer();
}
