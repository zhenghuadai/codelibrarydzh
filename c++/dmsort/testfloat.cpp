#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <vector>
#include <algorithm>
#include "mdtime.h"
#define SIZE 32768 
#include  "pthread.h"
#include <sched.h>
#include <math.h>
//_MM_ALIGN16 T array[SIZE];
#define FLT_MAX  3.402823466e+38F

typedef float T;
void quickSort(T This[],  unsigned int the_len);
typedef void (* sortAlg)(T*, unsigned int);
void binSort_byte(T *array,  unsigned int size);
#include "dmsortutil.hxx"
int Threads;
T  *ref_array,*cmp_array,*ref_array1;
T * originA;

int cmpfloat(const T& a, const T& b)
{
    return (a<b);
}

void checkRank(T *dst,int len,int *idx)
{
	int i;
	int err = 0;
	for(i =0;i<len-1;i++){
		if(dst[idx[i]] > dst[idx[i+1]]) {err ++;};
	}
	if(err == 0){
		printf("test Passed!\n");
	}else{
		printf("test Failed! %d\n",err);
	}
}

int main(int argc, char **argv) {
	 unsigned int size,sizeO,LocalSize,LocalPaddSize;
	size = SIZE;
	sizeO = SIZE;
	if(argc == 1){
		printf("usage: ./sort [size] [*factor] [-tn]\n");
		printf("	default size =32768; factor = 1;  \n");
		printf("	for example : ./sort 65536 *4 ; \n");
		printf("	then the size=65536*4; threads =2; \n");
		printf("	for example : ./sort 65536  -t2; \n");
		printf("	then the size=65536; threads =2; \n");
	}
	for( int i=1;i< argc;i++){
		if(argv[i][0] == '*'){ 
			sizeO *= atoi(argv[i]+ 1);
		}
		else{
			char* pfactor2 = strstr(argv[i],"*");
			if(pfactor2 == NULL)
				sizeO = atoi(argv[i]);
			else{
				sizeO = atoi(argv[i]) * atoi(pfactor2+1);
			}
		}
	}
	size = sizeO;

	T *array = (T*)_mm_malloc(size *sizeof(T),128);
	ref_array = (T*)_mm_malloc(size *sizeof(T),128);
	ref_array1 = (T*)_mm_malloc(size *sizeof(T),128);
	T *tmpTA  = (T*)_mm_malloc(size *sizeof(T),128);
	T *tmpTC  = (T*)_mm_malloc(size *sizeof(T),128);
	originA = (T*)_mm_malloc(size *sizeof(T),128);
	cmp_array = (T*)malloc(size *sizeof(T));
	//		int *cidx = new int[size];
	int *cidx  = (int*)_mm_malloc(2* size *sizeof(int),128);
	std::vector<T> cmp_vec(size);
	int testCase = 3;
	//while(testCase < 5) 
	{   
		if(testCase == 0){	
			printf("sorted\n");
			initData(array, sizeO);  
		}
		else if(testCase ==1){
			printf("reverse \n");
			initDataRev(array, sizeO);    
		}
		else {
			printf("rand\n");
			initDataRand(array, sizeO);   
		}

		memcpy(ref_array, array, size *sizeof(T));
		memcpy(ref_array1, array, size *sizeof(T));
		memcpy(originA, array, size *sizeof(T));
		cpA2V(array,cmp_vec,size);

		mdtime(0);
		quickSort(ref_array, size);
		printf("q   Sort     %f\t",mdtime(1)*1000);
		checkSort(ref_array, size);
		printf("\n");


		mdtime(0);
		std::sort(cmp_vec.begin(),cmp_vec.end()); 
		printf("std::sort    %f\t",mdtime(1)*1000);
		checkVec(cmp_vec);
		printf("\n");

		mdtime(0);
		std::sort(array, array+ size, cmpfloat); 
		printf("std::sort     %f\t",mdtime(1)*1000);
		checkSort(array, size);
		printf("\n");

		testSort(binSort_byte, array, size, "bin Sort     ");
		//printData(array, size);
#if  0
		if(Threads>1){		parallelSort(tmpTA,size);
			checkErr(tmpTA,size);
		}
#endif
		//		simpleRank(array,size,cidx);
next:
		testCase ++;
	}
	//printData(array, size);
	return 0;
}
