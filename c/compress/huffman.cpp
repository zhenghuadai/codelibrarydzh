/*
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 */
/*
 * =====================================================================================
 *
 *       Filename:  huffman.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年08月10日 22时04分18秒
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


huffNode* buildHuffmanTree(size_t* freq)
{

}


void huffmanS::getFreq(unsigned char* txt)
{
    unsigned char* p= txt;
    for(int i=0;i<256;i++)
        freq[i] =0;
    while(*p) {
        freq[*p++] ++;
    }
}
