/*
 * =====================================================================================
 *
 *       Filename:  testtypedef.c
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  05/28/2010 04:49:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

typedef int (*Lut_t)[65536];

int main()
{
 	Lut_t lut;
	int i;
	lut = (Lut_t) malloc( 3 * 65535 * sizeof(int));
	for(i =0;i<1024;i++){
		lut[0][i] = 0;
	}
}
