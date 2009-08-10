/*
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 */
/*
 * =====================================================================================
 *
 *       Filename:  huffman.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年08月10日 21时40分35秒
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

class huffmanS
{
    public:
        huffmanS(char* txt);
    public:
        void code(char* txt, char* ctxt);
        void decode(char* ctxt, char* txt);
    private:
        size_t freq[256]; 
        void getFreq(char* txt);
        
};
