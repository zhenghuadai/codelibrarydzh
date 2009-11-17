
#ifndef  ROUND_SSE__INC
#define  ROUND_SSE__INC

#include <xmmintrin.h>

#define MATH_SSE_FUNC_NAME(fn) fn

static double magic_delta=0.499999999999;

inline 
int     MATH_SSE_FUNC_NAME(dtoi)(double x) {
	return _mm_cvtsd_si32(_mm_load_sd(&x));
}

inline 
__int64 MATH_SSE_FUNC_NAME(dtol)(double x) {
	return _mm_cvtsd_si64(_mm_load_sd(&x));
}

inline 
int     MATH_SSE_FUNC_NAME(ftoi)(float x) {
	return _mm_cvtss_si32(_mm_load_ss(&x));
}

inline 
int      MATH_SSE_FUNC_NAME(dtoit)(double s) {
	return _mm_cvttsd_si32(_mm_load_sd(&s));
}

inline 
__int64  MATH_SSE_FUNC_NAME(dtolt)(double s) {
	return _mm_cvttsd_si64(_mm_load_sd(&s));
}

inline 
int MATH_SSE_FUNC_NAME(ftoit)(float s) {
	return _mm_cvttss_si32(_mm_load_ss(&s));
}


inline 
int MATH_SSE_FUNC_NAME(floor32)(double x) {
	double xx = x- matic_delta;
	return _mm_cvtsd_si32(_mm_load_sd(&xx));
} 

inline 
int MATH_SSE_FUNC_NAME(ceil32)(double x)  {
	double xx = x+ matic_delta;
	return _mm_cvtsd_si32(_mm_load_sd(&xx));
};

inline long MATH_SSE_FUNC_NAME(ftol)(float x) { 
}


#endif   /* ----- #ifndef ROUND_SSE__INC  ----- */
