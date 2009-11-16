#include <xmmintrin.h>
int trunk32(double s)
{
	return _mm_cvttsd_si32(_mm_load_sd(&s));
}


inline 
int dtoi(double x) {
	return _mm_cvtsd_si32(_mm_load_sd(&x));
}

inline 
int floor32(double x) {
} 

inline 
int ceil32(double x)  {
};

inline long ftol(float x) 
{ 
}


