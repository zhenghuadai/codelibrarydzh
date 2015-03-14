#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <vector>
#include <algorithm>
#include "mdtime.h"
#define SIZE 32 
#include  "pthread.h"
#include <sched.h>
#include <math.h>
#include "quick_cvsort.hxx"
#include "threadWrapper.h"
#include "threadPool.h"
//_MM_ALIGN16 T array[SIZE];
#define FLT_MAX  3.402823466e+38F
#define INT_MAX  (0xEFFFFFFF) 
#define __ALIGN__ __attribute__((aligned(128)))
typedef unsigned int T;
void quickSort(int This[],  unsigned int the_len);
void quickSort(unsigned int This[],  unsigned int the_len);
typedef void (* sortAlg)(T*, unsigned int);
void binSort(T *array,  unsigned int size);
void binSortSSE(T *array,  unsigned int size);
void binSortV(T *array,  unsigned int size);
void radixSort (T *source, unsigned int N);
void radixSort2 (T *source, unsigned int N);
void simpleQsort(unsigned int* begin, unsigned int size);
#include "dmsortutil.hxx"
int Threads;
T  *ref_array,*cmp_array,*ref_array1;
T * originA;
void initThread();
int main(int argc, char **argv) {
	unsigned int size,sizeO,LocalSize,LocalPaddSize;
	size = SIZE;
	sizeO = SIZE;
	if(argc == 1){
		printf("usage: ./sort [size] [*factor] ]\n");
		printf("	default size =32768; factor = 1;  \n");
		printf("	for example : ./sort 65536 *4 ; \n");
		printf("	then the size=65536*4;  \n");
		printf("	for example : ./sort 65536  ; \n");
		printf("	then the size=65536;  \n");
	}
    initThread();
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
		printf("quick Sort     %f\t",mdtime(1)*1000);
		checkSort(ref_array, size);
		printf("\n");


		mdtime(0);
		std::sort(cmp_vec.begin(),cmp_vec.end()); 
		printf("std::sort    %f\t",mdtime(1)*1000);
		checkVec(cmp_vec);
		printf("\n");

		mdtime(0);
		binSort(array, size);
		printf("bin Sort     %f\t",mdtime(1)*1000);
		checkSort(array, size);
		printf("\n");

		testSort(quickSort, array, size, "quick Sort   ");
		testSort(binSort, array, size,   "bin Sort     ");
		testSort(binSortSSE, array, size,"bin SortSSE  ");
		testSort(binSortSSE, array, size,"bin SortSSE  ");
		testSort(binSortV, array, size,  "bin SortV    ");
		testSort(qsortWrapper, array, size,"qsort        ");
        void binSort_byteXX(unsigned int *a, unsigned int n);
		testSort(binSort_byteXX, array, size,  "bin SortXX    ");
		testSort(cvQsortWrapper, array, size,  "icv Sort      ");
		testSort(simpleQsort, array, size,     "thread QSort  ");
#if  0
		if(Threads>1){		parallelSort(tmpTA,size);
			checkSort(tmpTA,size);
		}
#endif
next:
		testCase ++;
	}
	return 0;
}
