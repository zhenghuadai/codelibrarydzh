#include <functional>

//!
//!Example: defer({delete vec0; vec0= nullptr;});
//!
class Defer
{
#define __temp_name0(a) _defer ## a 
#define __temp_name(a) __temp_name0(a) 
#if defined(__COUNTER__)
#define __temp_id__ __COUNTER__
#else
#define __temp_id__ __LINE__
#endif
#define defer(x) Defer __temp_name(__temp_id__)([&](){x}); 
    typedef std::function<void(void)> F;
    public:
        Defer(F f):f(f){}
        ~Defer(){f();}
    private:
        F f;
};

