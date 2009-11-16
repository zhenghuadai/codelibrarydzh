#ifndef  SINCOS_TABLE__INC
#define  SINCOS_TABLE__INC

#ifdef USE_SSE2
#include <xmmintrin.h>
#endif

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#define tblFLOAT 4
#define tblDOUBLE 8

float tblSinf(double dAngle) ;// Returns sin with 20 bits of precision.
float tblCosf(double dAngle) ; // Returns cos with 20 bits of precision.
void tblSinCosf(double dAngle, float &dSin, float &dCos) ; // Returns cos with 20 bits of precision.

double tblSin(double dAngle) ;// Returns sin with 20 bits of precision.
double tblCos(double dAngle) ; // Returns cos with 20 bits of precision.
void tblSinCos(double dAngle, double &dSin, double &dCos) ; // Returns cos with 20 bits of precision.

static const double _TWOPOW32 = ((double)(65536.0 * 65536.0));

inline double _TWOPOW(int N) 
{
	return (((N) < 32) ? ((double)(1UL << (N))) : 
			((double)(1UL << (N - 32)) * _TWOPOW32))
		;
}


static const double g_MagicRoundingConstant =6755399441055744.0;// _TWOPOW(52) + _TWOPOW(51);
inline 
int Round(double x) {
#ifdef USE_SSE2
	return _mm_cvtsd_si32(_mm_load_sd(&x));
#else
	double mydtemp = (double)(x) + g_MagicRoundingConstant;
	return *(int*)&mydtemp;
#endif
}


#endif   /* ----- #ifndef SINCOS_TABLE__INC  ----- */

