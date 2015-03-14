#ifndef COMB_SORT_H_
#define COMB_SORT_H_

typedef float T;
extern void combSort(T *, int);
extern void combSort1(T *, int);
extern void combSort1_para(T *, int,float);
void sseCombSortStep1(T* a,int  size);
void preSort(T* a,int size);
void sseCombSort(T *a, int size);
void sseCombSort(T *a, int size,char*);

#define swap(a,b)	\
{	float tmp; tmp = a; a = b; b = tmp; }

#endif /*COMB_SORT_H_*/
