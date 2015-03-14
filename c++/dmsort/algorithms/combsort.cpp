#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include "comb_sort.h"
#include "mdtime.h"
#include "math.h"
#define SHRINK_FACTOR 1.3 



/*
void combSort(int *a, int len) {
int i, inc;
float dinc;

dinc = (float) len;
do {
dinc *= SHRINK_FACTOR;
inc = (int) dinc;
for (i = 0; i < len - inc; i++) {
if (a[i] > a[i + inc]) {
swap(a[i], a[i+inc]);
}
}

} while(inc > 1);

}
 */

static int newGap(int gap) {
    gap = (gap *10) / 13;
    if (gap == 9 || gap == 10) {
        gap = 11;
    } if (gap < 1) {
        gap = 1;
    } return gap;
}

void combSort(T *a, int size) {
    int gap = size;
    int i;
    int swapped = 0;
    for (;;) {
        gap = newGap(gap);
        swapped = 0;
        for (i = 0; i < size - gap; i++) {
            int j = i + gap;
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
                swapped = 1;
            }
        }
        if (gap == 1 && !swapped) {
            break;
        } 
    }
}

void combSort1(T *a, int size) {
    int gap = size;
    int i;
    int swapped = 0;
    float swap_num = 0;
mdtime(0);
    gap /= SHRINK_FACTOR;
    while (gap > 1) {
        for (i = 0; i < size - gap; i++) {
            if (a[i] > a[i + gap]) {
                swap(a[i], a[i + gap]);
            } 
        }
        gap /= SHRINK_FACTOR;
    }
    printf("1:%f\n",mdtime(1));
mdtime(0);
    for (;;) {
        swapped = 0;
        for (i = 0; i < size - 1; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
    printf("2:%f\n",mdtime(1));
}
void preSort(T* a,int size)
{
	for(int i=0;i< size/4;i++)
	{
	_MM_ALIGN16	float buf[16];
		buf[0] = a[i];
		buf[1]=  a[i+size/4];
		buf[2]=  a[i+size/2];
		buf[3]=  a[i+3*size/4];
		sseCombSortStep1(buf,4);
		a[i]         = buf[0];
		a[i+size/4]  = buf[1];
		a[i+size/2]  = buf[2];
		a[i+3*size/4]= buf[3];

	}
}
void combSort1_para(T *a, int size,float shrink_factor) {
	int gap = size/2.3;
	int i;
	int swapped = 0;
	float swap_num = 0;
	int loop1 = 0;
	int loop2 = 0;
	int ite= 0 ;
	int sh = shrink_factor;
	printf("shrink:%f \t",shrink_factor);
	mdtime(0);
	gap /= shrink_factor;
	while (gap>11) {
		for (i = 0; i < size - gap; i++) {
			if (a[i] > a[i + gap]) {
				swap(a[i], a[i + gap]);
			} 
		}
		gap /= shrink_factor;
		loop1 ++;
		/*
		gap *= 1.1;
		for (i =  size - gap -1; i>= 0; i--) {
			if (a[i] > a[i + gap]) {
				swap(a[i], a[i + gap]);
			} 
		}
		gap /= shrink_factor;
		   if(loop1 == 8 )
		  shrink_factor =  sqrt(shrink_factor) ;
		   if(loop1 == 16 )
		  shrink_factor =sh    ;
		  */
	}
	gap = 11;
	shrink_factor = 1.3;
	while (gap >1) {
		for (i = 0; i < size - gap; i++) {
			if (a[i] > a[i + gap]) {
				swap(a[i], a[i + gap]);
			} 
		}
		gap /= shrink_factor;
	}
	printf("1:%d:%f\t",loop1,mdtime(1));
	mdtime(0);
	for (;;) {
		swapped = 0;
		for (i = 0; i < size - 1; i++) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = 1;
			}
		}
		if (swapped == 0) {
			break;
		}
		loop2 ++;
	}
	printf("2:%d:%f\t",loop2,mdtime(1));

}
