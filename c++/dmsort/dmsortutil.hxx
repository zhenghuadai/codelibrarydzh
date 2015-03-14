#ifndef  DMSORTUTIL_INC
#define  DMSORTUTIL_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <vector>
#include <algorithm>
#include "mdtime.h"
#include  "pthread.h"
#include <sched.h>
#include <math.h>
#include "quick_cvsort.hxx"
#define FLT_MAX  3.402823466e+38F
#define INT_MAX  (0xEFFFFFFF) 
#define SIZE 32 
#define __ALIGN__ __attribute__((aligned(128)))

template <typename T>
void initData(T *data, int len) {
	int i;
		srand(time(NULL));
	for (i = 0; i < len; i++) {
		data[i] = (T)(i)  ;
		if (data[i] == 0) {
			data[i] = i;
		}
	}
}

template <typename T>
void PaddData(T *data, int start,int end) 
{
	for(int i = start;i<end;i++)
		data[i] = INT_MAX;
}

template <typename T>
void initDataRev(T *data, int len) {
	int i;
	srand(time(NULL));
	for (i = 0; i < len; i++) {
		data[i] = (T)(len-i) ;
		if (data[i] == 0) {
			data[i] = i;
		}
	}
}

template <typename T>
void initDataRand(T *data, int len) {
	int i;
	srand(517);
	//srand(time(NULL));
	for (i = 0; i < len; i++) {
		//   data[i] = (T)(len-i) / 1e3f;
		data[i] = (T)(rand()) ;
		if (data[i] == 0) {
			data[i] = i;
		}
	}
}

inline void print(int t){    printf("%d",t);}
inline void print(float t){  printf("%f",t);}
#define print4(a0, a1, a2, a3) {print(a0), printf(" ");print(a1), printf(" ");print(a2), printf(" ");print(a3);} 

template <typename T>
void cpA2V(T *data,std::vector<T> & dst, unsigned int size)
{
	int i;
	for(i=0;i<size;i++)
		dst[i] = data[i];
}

template <typename T>
void printData(T *data, int len) {
	int i;
	for (i = 0; i < len; i += 4) {
		if(i% 8 ==0) printf("\n");
		print4(data[i], data[i + 1], data[i + 2], data[i + 3])
	}
	printf("\n");
}

template <typename T>
void checkSortP(T *dst,int len)
{
	int i;
	int err = 0;
	for(i =0;i<len-1;i++){
		if(dst[i] > dst[i+1]) {err ++;printf("<");print4(i,dst[i],dst[i+1],dst[i+2]);printf(">");};
	}
	if(err == 0){
		printf("test Passed!\n");
	}else{
		printf("test Failed! %d\n",err);
	}
}

template <typename T>
void checkSortP(T *dst,int len,int *idx)
{
	int i;
	int err = 0;
	for(i =0;i<len-1;i++){
		if(dst[idx[i]] > dst[idx[i+1]]) {err ++;print4(idx[i],dst[idx[i]],idx[i+1],dst[idx[i+1]]);printf("\n");};
	}
	if(err == 0){
		printf("test Passed!\n");
	}else{
		printf("test Failed! %d\n",err);
	}
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkRank
 *  Description:  Check if the array is ranked?
 *  	  Input:  
 *       Output:
 *      Example:  
 * =====================================================================================
 */
template <typename T>
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

template <typename T>
void checkSort(T *dst,int len)
{
	int i;
	int err = 0;
	for(i =0;i<len-1;i++){
		if(dst[i] > dst[i+1]) {err ++;};
	}
	if(err == 0){
		printf("test Passed!\n");
	}else{
		printf("test Failed! %d\n",err);
	}
}

template <typename T>
void diffArray(T *data1, T *data2, int len) {
	int flag = 0;
	int i;
	for (i = 0; i < len; i++) {
		if (data1[i] != data2[i]) {
			print(data1[i]);
            printf(" ");
			print(data2[i]);
            printf("\n");
			flag = 1;
		}
	}
	if (flag == 1) {
		printf("test Failed!\n");
	} else {
		printf("test Passed!\n");
	}
}

template <typename T>
int checkVec(std::vector<T> & dst)
{
	int i;
	int err = 0;
	for(i =0;i<  dst.size()-1;i++){
		if(dst[i] > dst[i+1]) err++;	
	}
	if(err == 0){
		printf("test Passed!\n");
	}else{
		printf("test Failed! %d\n",err);
	}
}

//!----------------------------------------------------------------------------
//! the wrapper of qsort fot T
//!----------------------------------------------------------------------------
template <typename T>
int cmp(const void* a, const void* b)
{
    return (*(T*)a - *(T*)b);
}

template <typename T>
void qsortWrapper(T* array, unsigned int size)
{
    qsort(array, size, sizeof(array[0]), cmp<T>);
}


//!----------------------------------------------------------------------------
//! the wrapper of cvsort fot T
//!----------------------------------------------------------------------------
template <typename T>
int cmp(const T& a, const T& b)
{
    return (a<b);
}

template <typename T>
void cvQsortWrapper(T* array, unsigned int size)
{
    cvQsort<T,cmp>(array, size);
}


#ifndef  LOOPTEN
#define  LOOPTEN 1
#endif 
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  testSort
 *  Description:  The frame of test sorting algorithm
 *  	  Input:  
 *       Output:
 *      Example:  testSort
 * =====================================================================================
 */
template <typename T>
void testSort(sortAlg alg, T* array,  unsigned int size, char* msg)
{
	double t3 = 0.0;
	for(int i=0;i< LOOPTEN;i ++){
		initDataRand(array, size);   
		mdtime(0);
		alg(array, size);
		t3 += mdtime(1) * 1000;
	}
	printf("%s%f\t",msg,t3/LOOPTEN);
	checkSort(array, size);
	printf("\n");
}
#endif   /* ----- #ifndef dmsortutil_INC  ----- */
