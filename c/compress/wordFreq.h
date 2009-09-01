/*
 * =====================================================================================
 *
 *       Filename:  wordFreq.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/01/2009 04:53:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

class Node;
class WordFreq
{
private:
	Node* pHead;
public:
	WordFreq():pHead(0){}
	~WordFreq(){destroy();}
	void destroy();
	void stat(char* txt);
	void print();
};
