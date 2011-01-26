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

