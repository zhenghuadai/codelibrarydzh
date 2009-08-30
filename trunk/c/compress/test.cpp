/*
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 */
/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  :w
 *
 *        Version:  1.0
 *        Created:  2009年08月23日 15时44分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gmail.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

char * Getsubjectfromfile(char *pfname);
int main(int argc, char** argv)
{
    char* txt; 
    HuffmanS hf;
    txt = Getsubjectfromfile(argv[1]);
    hf.buildTree((unsigned char*)txt);

}
