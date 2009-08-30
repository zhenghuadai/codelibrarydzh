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
#include <malloc.h>
#define armLeft 0
#define armRight 1
class HuffNode{
	private:
	public:
		unsigned long long freq;
		unsigned char ch;
		unsigned char len;
        unsigned char arm;
        unsigned char reserved;
		unsigned int hCode;
		HuffNode* left;
		HuffNode* right;
		HuffNode* parent;
	public:
        HuffNode():freq(0), ch(0), len(0), arm(0), hCode(0), left(0), right(0), parent(0){ }
    public:
    static int compareHuffNode( const void * node1, const void* node2){
        return (((HuffNode*)node1)-> freq < ((HuffNode*)node2)->freq ? 1:-1);
    }
};

class Link{
	public:
		HuffNode* node;
		Link* next;
};


class HuffmanS
{
	private:
		unsigned long long freq[256]; 
		void* head;
		unsigned int codeTable[256];
        unsigned char codeLen[256];
        HuffNode mNodes[1024];
	public:
		HuffmanS(char* txt);
		HuffmanS(){};
	public:
		void code(char* txt, char* ctxt);
		void decode(char* ctxt, char* txt);
	public:
		void* buildTree(size_t* freq);
		void* buildTree(unsigned char* txt);
		void getFreq(unsigned char* txt);
	private:
		void hSort(void* hnode);
		void hSort(unsigned long long *f);
        void hSortFromFrq();
};
