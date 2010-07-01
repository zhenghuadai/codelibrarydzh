#include <stdio.h>
#include "rdtsc.h"
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
}
