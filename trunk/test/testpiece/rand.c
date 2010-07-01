#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rdtsc.h"
int main()
{
int s ;
int i;
srand(time(0));
for(i=0;i<10;i++){
printf("%d\n", rand());
}

}

