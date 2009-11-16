#include <math.h>
#include "sincos.h"
#include <stdio.h>
#include <stdlib.h>

void test1()
{
	double src = M_PI/4;
	double SQRT2_2 = sqrt(2)/2;
	double dstsinf = sinf(src);
	double dstsin = sin(src);
	double dsttbsin = tblSin(src);
	double dsttbsinf = tblSinf(src);
	//printf("%32f \n", SQRT2_2);
	printf("sinf   %32f \n", dstsinf );
	printf("sin    %32f \n", dstsin );
	printf("tbsin  %32f \n", dsttbsin );
	printf("tbsinf %32f \n", dsttbsinf );
}

int main()
{
	test1();
}
