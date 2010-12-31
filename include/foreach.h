/*
 * =====================================================================================
 *
 *       Filename:  foreach.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/31/2010 03:58:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#define _for_each2(a, vec, x) {\
    typeadapter<typeof(vec)>::iterator i ;\
    for(i=vec.begin(); i!=ivec.end();i++){\
        typeadapter<typeof(vec)>::value_type &a = *i;\
        x;\
    }\
}
#define in ,
#define for_each2(a, x) _for_each2(a, x)
/* for example 
   int ia[] = {1, 2, 3};
   vector<int> ivec(ia, ia + sizeof(ia) / sizeof(int));

   for_each(ivec.begin(), ivec.end(), printElem);
   for_each2(a in ivec, ({
   cout<< a << endl;
   ;}));
*/

