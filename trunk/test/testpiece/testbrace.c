#include <stdio.h>
#include "rdtsc.h"
int f()
{
    int a,b,c;
    return ({int e;a=b+c; a;});
}
int main()
{
	unsigned long long a ,b ,c;
	mdtime(0);
	printf("%f\n", mdtime(1));
	a = cast2u64(getrdtsc());
	b = cast2u64(getrdtsc());
	printf("%d\n", b -a );
	startTime();
	printf("%d\n", endTime());
    c = (a=b, endTime(), 2);
    c = ({a=b, endTime() ;a;});
	printf("%d\n", c );
}
