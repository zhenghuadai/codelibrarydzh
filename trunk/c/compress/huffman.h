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

class huffNode{
	private:
		unsigned long long freq;
		unsigned char ch;
		unsigned char len;
		unsigned int hcode;
		huffNode* left;
		huffNode* right;
		huffNode* parent;
	public:

};

class link{
	public:
		link* next;
		void* node;
};


class huffmanS
{
	private:
		unsigned long long freq[256]; 
		void* head;
		unsigned int codeTable[256];
	public:
		huffmanS(char* txt);
	public:
		void code(char* txt, char* ctxt);
		void decode(char* ctxt, char* txt);
	public:
		virtual void* buildTree(size_t* freq);
		void* buildTree(char* txt);
		void getFreq(char* txt);
	private:
		void hSort(void* hnode);
		void hSort(unsigned long long *f);
};
