/*
 * =====================================================================================
 *
 *       Filename:  testmemcpy.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/01/2010 03:23:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include "memcpy.c"

#define MAX 32
#define TIMES 100

#define CPUTIME (getrusage(RUSAGE_SELF,&ruse),\
		ruse.ru_utime.tv_sec + ruse.ru_stime.tv_sec + \  
		1e-6 * (ruse.ru_utime.tv_usec + ruse.ru_stime.tv_usec)) 

	struct rusage ruse;

	extern int getrusage();

	typedef struct { unsigned char dummy [32]; } DT;
#define copy1 \
		*dest = *source;\
	dest++;\
	source++; 

#define copy2 \
		*(unsigned short *)dest = *(unsigned short *)source;\
	dest += 2;\
	source += 2; 

#define copy4 \
		*(unsigned int *)dest = *(unsigned int *)source;\
	dest += 4;\
	source += 4;\ 

#define copy8 \
		*(unsigned long *)dest = *(unsigned long *)source;\
	dest += 8;\
	source += 8;


void mycopy( unsigned char * dest, unsigned char * source, size_t s ){
	size_t bytes = 0;
	while ( s ){
		switch( s ){
			case 1 : {
						 copy1;
						 s--;
						 break;
					 }
			case 2 : {
						 copy2;
						 s -= 2;
						 break;
					 }
			case 3 : {
						 copy2;
						 copy1;
						 s -= 3;
						 break;
					 }
			case 4 : {
						 copy4;
						 s -= 4;
						 break;
					 }
			case 5 : {
						 copy4;
						 copy1;
						 s -= 5;
						 break;
					 }
			case 6 : {
						 copy4;
						 copy2;
						 s -= 6;
						 break;
					 }
			case 7 : {
						 copy4;
						 copy2;
						 copy1;
						 s -= 7;
					 }
			default : {
						  copy8;
						  s -= 8;
					  }
		}
	}
}

void fastcpy(unsigned char* dst, unsigned char* src, size_t s) 
{
	unsigned char* sa = src+s;
	DT *d1 = (DT*)dst - 1;
	DT *s1 = (DT*)src - 1;
	size_t si = s / sizeof(DT);

	si = (si + 7) / 8;
	switch(si % 8) 
	{
		case 0: do { *++d1 = *++s1;
					case 7:      *++d1 = *++s1;
					case 6:      *++d1 = *++s1;
					case 5:      *++d1 = *++s1;
					case 4:      *++d1 = *++s1;
					case 3:      *++d1 = *++s1;
					case 2:      *++d1 = *++s1;
					case 1:      *++d1 = *++s1;
				} while(--si > 0);
	}

	dst = (unsigned char*)d1;
	src = (unsigned char*)s1;
	while(src < sa) 
	{
		*++dst = *++src;
	}
}
int main(void)
{
	char *s1, *s2, *s3;
	unsigned int size;
	double t0, t1;
	unsigned int i;

	size = MAX*1024*1024;
	s1 = malloc(size);
	s2 = malloc(size);
	// s3 = malloc(size);

	s1[size-1] = 1;
	s2[size-1] = 2;
	// s3[size-1] = 3;

	t0 = CPUTIME;
	for ( i = 0; i < TIMES; i++ ){
		memcpy(s1, s2, size);
	}
	t1 = CPUTIME;
	printf("CPU time = %f secs.\n",t1-t0);
	t0 = CPUTIME;
	for ( i = 0; i < TIMES; i++ ){
		fastcpy(s1, s2, size);
	}
	t1 = CPUTIME;
	printf("CPU time = %f secs.\n",t1-t0);

	t0 = CPUTIME;
	for ( i = 0; i < TIMES; i++ ){
		mycopy(s1, s2, size);
	}
	t1 = CPUTIME;
	printf("CPU time = %f secs.\n",t1-t0);

	t0 = CPUTIME;
	for ( i = 0; i < TIMES; i++ ){
		memcpy_1(s1, s2, size);
	}
	t1 = CPUTIME;
	printf("CPU time = %f secs.\n",t1-t0);

}
