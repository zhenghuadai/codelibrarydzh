
static const double _TWOPOW32 = ((double)(65536.0 * 65536.0));
static const double g_MagicRoundingConstant =6755399441055744.0;// _TWOPOW(52) + _TWOPOW(51);

inline double _TWOPOW(int N) 
{
	return (((N) < 32) ? ((double)(1UL << (N))) : 
			((double)(1UL << (N - 32)) * _TWOPOW32))
		;
}

inline 
int dtoi(double x) {
	double mydtemp = (double)(x) + g_MagicRoundingConstant;
	return *(int*)&mydtemp;
}

inline 
long dtol(double x) {
	double mydtemp = (double)(x) + g_MagicRoundingConstant;
	return *(long*)&mydtemp;
}

inline long ftol(float x) 
{ 
	static const float magic_f = (3<<21);
	static const long magic_i = 0x4ac00000;
	float ftmp=x+magic_f;
	return  (*((long*)&ftmp)-magic_i) >> 1; 
}

inline 
int floor32(double x) {
	double mydtemp = (double)(x) + g_MagicRoundingConstant;
	int val = *(int*)&mydtemp;
	if (val > x) --val;
	return val;
} 

inline 
int ceil32(double x)  {
	double mydtemp = (double)(x) + g_MagicRoundingConstant;
	int val = *(int*)&mydtemp;
	if (val < x) ++val;
	return val;
};



