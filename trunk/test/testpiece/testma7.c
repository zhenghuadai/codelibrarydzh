/*
 * =====================================================================================
 *
 *       Filename:  testma7.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/03/2010 03:13:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#define test(a, b, c) struct ## a ## b ## c

test(int)
test(int, char)
test(int , int,char)
