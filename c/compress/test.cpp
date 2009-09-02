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
#include "wordFreq.h"
char * Getsubjectfromfile(char *pfname);
int main(int argc, char** argv)
{
    char* txt; 
    HuffmanS hf;
	if(argc ==1) return 1;
    txt = Getsubjectfromfile(argv[1]);
    int txtLen = strlen(txt);
    char* ctxt = new char[txtLen+1];
    size_t bits= hf.code(txt, txtLen, ctxt);
    FILE* fpout;
    fpout= fopen("code.hz", "w");
    fwrite(ctxt,(bits>>3)+1, 1, fpout );
    fclose(fpout);
    delete ctxt;

	WordFreq wf;
    wf.start();
	wf.stat(txt);
    wf.end();
	wf.print();
}
