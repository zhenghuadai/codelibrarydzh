/*
 * =====================================================================================
 *
 *       Filename:  testma5.c
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  05/18/2010 09:20:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#define Str(x) #x
#define Str2(x) Str(x)
#define ecx_ c
#define inRistrict(x) =##x
#define A(x) x##_ 
#define masm__m2E(x, e, m)       __asm__("" : Str2(inRistrict(A(e)))(m)::);

masm__m2E(mov, ecx, x);
