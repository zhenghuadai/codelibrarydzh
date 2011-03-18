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
#define _for_each2(a, vec, x) {\
    typeadapter<typeof(vec)>::iterator i ;\
    for(i=vec.begin(); i!=ivec.end();i++){\
        typeadapter<typeof(vec)>::value_type &a = *i;\
        x;\
    }\
}
#define in ,
#define for_each2(a, x) _for_each2(a, x)
/**  @} */
#define MAX_LINE_SIZE 4096
#define _file_foreach(a, fn, x) {\
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
#define file_foreach(a, x) _file_foreach(a, x)


