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
#include "string.h"
#include "wordFreq.h"
#define WORD_NEW 1
#define WORD_EXIST 0
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
        int add(char* str, int len);
        int add(char* str){add(str, strlen(str));}
        Node* add(char tC);
        void inc(){freq ++;}
    private:
        void addSib(Node* tSib);
        void addChild(char*str, int len);
        void addSibNew(char* str, int len);
        Node* addSibNew(char tC);
        void addChildNew(char* str, int len);
        Node* find(char tC);
};

void Node::addSib(Node* tSib)
{
    tSib ->mSib = mSib;
    mSib = tSib;
}

Node* Node::find(char tC)
{
    Node* pSib = this;
    while(pSib && pSib->c != tC) pSib = pSib->mSib;
    return pSib;
}

Node* Node::addSibNew(char tC)
{
    Node* tNode = new Node(tC);
    addSib(tNode);
    return tNode;
}

Node* Node::add(char tC)
{
    Node* pSib = this;
    pSib = find(tC);
    if (pSib ==NULL)
        pSib = addSibNew(tC);
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

void Node::addChildNew(char* str, int len)
{
    //if(len ==0) return;
    int i=0;
    Node* tNode;
    tNode= this; 
    while(i<len){
        tNode->mChild = new Node(str[i++]);	
        tNode = tNode->mChild;
    }
    tNode -> inc();
}


void Node::addSibNew(char* str, int len)
{
    int i=0;
    //if(len ==0) return;
    Node* tNode;
    tNode= addSibNew(str[0]);
    if(len > 1)
        tNode -> addChildNew(str+1, len-1); 
    else 
        tNode -> inc();

}

int Node::add(char* str, int len)
{
#if 0
    Node* tNode;
    if(len ==0) return;
    tNode = add(*str);
    if( len >1) 
        tNode -> addChild(str+1 ,len -1);
    else if(len ==1)
        tNode -> inc();
#else 
    Node* tNode=this;
    Node* pNode =this;
    int tLen = 0;
    while((tLen <len )&&(pNode) && ((tNode = pNode->find(str[tLen])) !=NULL))
    { 
        tLen ++;
        pNode = tNode->mChild;
    }
    if(tLen == len) { tNode->inc(); if(tNode->freq ==1 ) return WORD_NEW; else return WORD_EXIST;}
    if( pNode == NULL){
        tNode -> addChildNew(str+ tLen , len - tLen );
    } else if (tNode ==NULL){
        pNode -> addSibNew(str+ tLen, len - tLen);
    }
    return WORD_NEW;
#endif
}
/************************************************************************
 *
 *
 *
 * *********************************************************************/
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
void printStr(char* pStart, int len)
{
    printf("<");
    for(int i=0;i<len; i++) printf("%c", *(pStart+i));
    printf(">\n");
}

void WordFreq::start()
{
    destroy();	
    pHead = new Node();
}

void WordFreq::stat(char* txt)
{
    char* pStart = txt;
    char* pEnd = txt;
    while(*pEnd){
        if (isSeperator(*pEnd)){
            int len = pEnd - pStart ;
            int ret;
            if((len>0) && (len < 1024)){
                ret =pHead -> add(pStart, len);
                if(ret){
                    words ++;
                    //printStr(pStart, len);
                    chNum += (len+1);
                }
            }
            wordNumTotal++;
            pEnd++;
            pStart =pEnd; 
        } else 
            pEnd ++;
    }
}

void WordFreq::end()
{
    getFreq();
    this ->sort();
}

void WordFreq::visitNode(Node* tNode, int level)
{
    static char strBuf[1024];
    strBuf[level] = tNode->c;
    //printf("<%d %c %d %0x %0x >", level, tNode->c, tNode->freq, tNode->mChild, tNode->mSib);
    if(tNode -> freq >0){
        strBuf[level+1] =0;
        //printf("%6d %s\n", tNode->freq, strBuf);
        appandEntry(strBuf, tNode->freq);
    }
}

void WordFreq::traversTree(Node* root, int level)
{
    if(!root) return ;
    visitNode(root, level);
    traversTree(root->mChild, level+1);
    traversTree(root->mSib, level);
}

void WordFreq::print()
{
    printf("words :%d \n", words);
    printf("total words :%d \n", wordNumTotal);
    //traversTree(pHead, 0);
    for(int i=0;i< words;i++)
        printf("%6d %s\n", mEntry[i].freq, mEntry[i].str);

}

void WordFreq::getFreq()
{
    if( strPoolSize < chNum) {
        if(strPool) delete strPool;
        strPool = new char[chNum];
        strPoolSize = chNum;
    }
    if( mEntrySize < words){
        if(mEntry) delete mEntry;
        mEntry = new Entry[words];
        mEntrySize = words;
    }
    tEntryIndex = 0;
    tPstr = strPool;
    traversTree(pHead,0);
}

void WordFreq::appandEntry(const char* str, size_t freq)
{
    if(( tEntryIndex >= mEntrySize ) || (tPstr-strPool >= strPoolSize)){
        printf(" buf overflow\n");
        exit(0);
    }
    strcpy(tPstr, str);
    mEntry[tEntryIndex++].set(tPstr, freq);
    tPstr += (strlen(str)+1);
}

void WordFreq::destroy()
{
    if(pHead) delete pHead ; pHead =0;
    words = wordNumTotal = chNum = 0;
    //if(mEntry) delete mEntry;
    //if(strPool) delete strPool;
}


void WordFreq::sort(int key)
{
    qsort(mEntry, words, sizeof(Entry), Entry::compareFreq);
}
