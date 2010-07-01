/*
 * =====================================================================================
 *
 *       Filename:  testrand.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/20/2010 11:49:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <time.h>

unsigned int f()
{
 __asm__("rdtsc");
}
unsigned long long l()
{
 __asm__("rdtsc");
}
int main(int argc, char** argv)
{
	unsigned int seed ;
	unsigned long long leed ;
	char* in =0;
	if(argc ==2)
		in = argv[1];
	seed = f();
	leed = l();
	srand(leed%(1024*1024));
	if(in !=0){
		int len = strlen(in);
		int i = len /4;
		int seed2 = *(int*) in;
		for(i=1;i<len/4; i++)
			seed2 ^= ((int*)in)[i];

		leed += seed2;
	srand(leed%(1024*1024));
	}
	printf("%u\n", rand()%100);
	//	printf("%llx\n", leed);
}
