/*
 * =====================================================================================
 *
 *       Filename:  wordFreq.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/01/2009 08:54:09 PM
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
typedef unsigned int U32;
#include "wordFreq.h"
class Node
{
public:
	size_t freq;
	union{
		char c;
		U32 u32;
	};
	Node* mChild;
	Node* mSib;
public:
	Node():freq(0),c(0),mChild(0),mSib(0){}
	Node(char tC):freq(0),c(tC),mChild(0),mSib(0){}
	~Node(){if(mChild) delete mChild; if(mSib) delete mSib;}
public:
	void add(char* str);
    void add(char* str, int len);
    Node* add(char tC);
    void inc(){freq ++;}
    void addSib(Node* tSib);
private:
    void  addChild(char*str, int len);
};

void Node::addSib(Node* tSib)
{
    tSib ->mSib = mSib;
    mSib = tSib;
}

Node* Node::add(char tC)
{
    Node* pSib = this;
    while(pSib && pSib->c != tC) pSib = pSib->mSib;
    if(!pSib) {
        Node* tNode = new Node(tC);
        addSib(tNode);
        pSib = tNode;
    }
    return pSib;

}

void  Node::addChild(char*str, int len)
{
    if( mChild ==0){
        mChild = new Node(*str);
        if(len ==1) {
            mChild -> inc(); 
            return ;
        }
        mChild ->addChild(str+1, len-1);
    }else{
        mChild->add(str, len);
    }
}

void Node::add(char* str, int len)
{
    Node* tNode;
    if(len ==0) return;
    tNode = add(*str);
    if( len >1) 
        tNode -> addChild(str+1 ,len -1);
    else if(len ==1)
        tNode -> inc();
}

void Node::add(char* str)
{
#if 1
    char* pstr = str+1;
    Node* tNode;
    if(*str)
        tNode = add(*str);
    if(*pstr)	
        tNode->add(pstr);
    else
        tNode->inc();
#else
    //while(*pstr){
    //	char tC = *pstr;
    //	
    //	pstr++;
    //}
#endif
}

inline int  isDigit(char c) {
    return (( c >= '0') &&(c <='9'))? 1:0;
}

inline int  isAlpha(char c){
    return (( c >= 'A') &&(c <='z'))? 1:0;
}
inline int  isConnector(char c)
{
    if((c=='_') ) return 1;
    return 0;
}

int isSeperator(char c)
{
    if( isDigit(c) || isAlpha(c) || isConnector(c))
        return 0;
    else 
        return 1;
}

void WordFreq::stat(char* txt)
{
    destroy();	
    pHead = new Node(*txt);
    char* pStart = txt;
    char* pEnd = txt;
    while(*pEnd){
        if (isSeperator(*pEnd)){
            int len = pEnd - pStart ;
            {
                //for(int i=0;i<len; i++) printf("%c", *(pStart+i));
                //printf("\n");
            }
            if((len>0) && (len < 1024))
                pHead -> add(pStart, len);
            pEnd++;
            pStart =pEnd; 
        } else 
            pEnd ++;
    }
}

static char strBuf[1024];
static void visitNode(Node* tNode, int level)
{
    strBuf[level] = tNode->c;
    //printf("<%d %c %d %0x %0x >", level, tNode->c, tNode->freq, tNode->mChild, tNode->mSib);
    if(tNode -> freq >0){
        strBuf[level+1] =0;
        printf("%6d %s\n", tNode->freq, strBuf);
    }
}

static void traversTree(Node* root, int level)
{
    if(!root) return ;
    visitNode(root, level);
    traversTree(root->mChild, level+1);
    traversTree(root->mSib, level);
}

void WordFreq::print()
{
    traversTree(pHead, 0);
}

void WordFreq::destroy()
{
    if(pHead) delete pHead ; pHead =0;
}
