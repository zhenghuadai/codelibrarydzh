/*
 * =====================================================================================
 *
 *       Filename:  test++.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  05/17/2010 03:25:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include	<pthread.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
int f(int x)
{
 x++;
 return x;
}

int y = 0;
int x;

pthread_t thread_table[32];
pthread_barrier_t thread_barrier;
void* pfunc(void*){
	int i;
	pthread_barrier_wait(&thread_barrier);
	printf("YYYYYYYYYYY%d\n", y);
	__asm("lea %0, %%esi"::"m"(y));
	for(i =0;i<100000;i++){
		x = rand();
	//	++y;
	//__asm("addl $1,  (%%esi)"::);
	__asm("lock incl %0":"+m"(y):);
	}
}

int main(int argc, char** argv)
{
	int x = 0;
	if(argc>1) x = atoi(argv[1]);
	x= f(x);
	x++;
	printf("%d\n", x);
	++x;
	printf("%d\n", x);

	printf("%d\n", y);
	printf("addr Y:%0x\n", &y);
	__asm("lea %1, %%eax":"=a"(x):"m"(y));
	printf("addr Y:%0x\n", x);
	pthread_barrier_init(&thread_barrier, NULL, 2);
	pthread_create(&thread_table[0], NULL, pfunc, NULL);
	pthread_create(&thread_table[1], NULL, pfunc, NULL);
	pthread_join(thread_table[0],NULL);
	pthread_join(thread_table[1],NULL);
printf("y:%d\n",y);
}
