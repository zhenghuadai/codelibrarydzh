/**
 * =====================================================================================
 *       @file    foreach.h
 *
 *       @brief   '
 *
 *       @author  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *       @version 1.0
 *       @date    01/19/2011 08:16:40 PM
 *
 *       Revision none
 *       Compiler gcc
 *       Company  
 * =====================================================================================
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
#define CAPI
#define CSTATIC
#define in ,
template<class T>
class typeadapter{
    public: 
        typedef typename T::iterator iterator;    
        typedef typename T::value_type value_type ;    

        static size_t size(T& t, size_t _sizeofT){ return t.size(); }
        static iterator start(T& t){    return t.begin();}
};

template<class T>
class typeadapter<T*>{
    public: 
        typedef T* iterator;    
        typedef T value_type;    

        static size_t size(T* const t, size_t sizeoft){ return 1; }
        static T* start(T* t){    return t;}
};

template<>
class typeadapter<char*>{
    public: 
        typedef char* iterator;    
        typedef char value_type;    

        static size_t size(char* const t, size_t sizeoft){ return strlen(t); }
        static char* start(char* t){    return t;}
};



template<class T, int N>
class typeadapter<T[N]>{
    public: 
        typedef T* iterator;    
        typedef T value_type;    

        static size_t size(T* const t, size_t sizeoft){   return N;  }
        static T* start(T* t){    return t;}
};


/**
* @name 
  @example 
   int ia[] = {1, 2, 3};
   vector<int> ivec(ia, ia + sizeof(ia) / sizeof(int));

   for_each(ivec.begin(), ivec.end(), printElem);
   for_each2(a in ivec, ({
   cout<< a << endl;
   ;}));
 * @{ */
    //for(i=vec.begin(); i!=ivec.end();i++){\
    
#define _for_each2(a, vec, x) {\
    typeadapter<typeof(vec)>::iterator _m_it ;\
    int _m_i;\
    size_t _m_end = typeadapter<typeof(vec)>::size(vec, sizeof(vec));\
    for(_m_i=0, _m_it=typeadapter<typeof(vec)>::start(vec)/*  vec.begin()*/; _m_i<_m_end;_m_i++, _m_it++){\
        typeadapter<typeof(vec)>::value_type &a = *_m_it;\
        x;\
    }\
}

CAPI
#define foreach(a, x) _for_each2(a, x)

#define $_ ({
#define _$ ;})
/**  @} */

#define MAX_LINE_SIZE 4096
#define _file_foreach_line(a, fn, x) {\
    char* a;\
    FILE* infp;\
    infp=fopen(fn, "r");\
    a= (char*) malloc(MAX_LINE_SIZE);\
    if(infp ==NULL){\
        printf("can not open %s\n",fn);\
    }else{\
        while( fgets(a,MAX_LINE_SIZE,infp)!=NULL){\
            x;\
        }\
        fclose(infp);\
        free(a);\
    };\
}

#define _file_foreach_byte(a, fn, x) {\
    char a;\
    FILE* infp;\
    infp=fopen(fn, "r");\
    if(infp ==NULL){\
        printf("can not open %s\n",fn);\
    }else{\
            while(((a=fgetc(infp))!=EOF) ){\
            x;\
        }\
        fclose(infp);\
    };\
}


CAPI 
#define file_eachline(a, x) _file_foreach_line(a, x)
#define file_eachbyte(a, x) _file_foreach_byte(a, x)


