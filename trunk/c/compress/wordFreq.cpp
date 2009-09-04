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
#define WORD_NONE  1
void TrieNode::addSib(TrieNode* tSib)
{
    tSib ->mSib = mSib;
    mSib = tSib;
}

TrieNode* TrieNode::find(char tC)
{
    TrieNode* pSib = this;
    while(pSib && pSib->c != tC) pSib = pSib->mSib;
    return pSib;
}

TrieNode* TrieNode::addSibNew(char tC)
{
    TrieNode* tTrieNode = new TrieNode(tC);
    addSib(tTrieNode);
    return tTrieNode;
}

TrieNode* TrieNode::add(char tC)
{
    TrieNode* pSib = this;
    pSib = find(tC);
    if (pSib ==NULL)
        pSib = addSibNew(tC);
    return pSib;

}

void  TrieNode::addChild(char*str, int len)
{
    if( mChild ==0){
        mChild = new TrieNode(*str);
        if(len ==1) {
            mChild -> inc(); 
            return ;
        }
        mChild ->addChild(str+1, len-1);
    }else{
        mChild->add(str, len);
    }
}

void TrieNode::addChildNew(char* str, int len)
{
    //if(len ==0) return;
    int i=0;
    TrieNode* tTrieNode;
    tTrieNode= this; 
    while(i<len){
        tTrieNode->mChild = new TrieNode(str[i++]);	
        tTrieNode = tTrieNode->mChild;
    }
    tTrieNode -> inc();
}


void TrieNode::addSibNew(char* str, int len)
{
    int i=0;
    //if(len ==0) return;
    TrieNode* tTrieNode;
    tTrieNode= addSibNew(str[0]);
    if(len > 1)
        tTrieNode -> addChildNew(str+1, len-1); 
    else 
        tTrieNode -> inc();

}

int TrieNode::search(char* str, int len)
{
    TrieNode* tTrieNode=this;
    TrieNode* pTrieNode =this;
    int tLen = 0;
    while((tLen <len )&&(pTrieNode) && ((tTrieNode = pTrieNode->find(str[tLen])) !=NULL))
    { 
        tLen ++;
        pTrieNode = tTrieNode->mChild;
    }
    if(tLen == len) { return WORD_EXIST;}
	return WORD_NONE;
}

int TrieNode::add(char* str, int len)
{
#if 0
    TrieNode* tTrieNode;
    if(len ==0) return;
    tTrieNode = add(*str);
    if( len >1) 
        tTrieNode -> addChild(str+1 ,len -1);
    else if(len ==1)
        tTrieNode -> inc();
#else 
    TrieNode* tTrieNode=this;
    TrieNode* pTrieNode =this;
    int tLen = 0;
    while((tLen <len )&&(pTrieNode) && ((tTrieNode = pTrieNode->find(str[tLen])) !=NULL))
    { 
        tLen ++;
        pTrieNode = tTrieNode->mChild;
    }
    if(tLen == len) { tTrieNode->inc(); if(tTrieNode->freq ==1 ) return WORD_NEW; else return WORD_EXIST;}
    if( pTrieNode == NULL){
        tTrieNode -> addChildNew(str+ tLen , len - tLen );
    } else if (tTrieNode ==NULL){
        pTrieNode -> addSibNew(str+ tLen, len - tLen);
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
    pHead = new TrieNode();
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

void WordFreq::visitTrieNode(TrieNode* tTrieNode, int level)
{
    static char strBuf[1024];
    strBuf[level] = tTrieNode->c;
    //printf("<%d %c %d %0x %0x >", level, tTrieNode->c, tTrieNode->freq, tTrieNode->mChild, tTrieNode->mSib);
    if(tTrieNode -> freq >0){
        strBuf[level+1] =0;
        //printf("%6d %s\n", tTrieNode->freq, strBuf);
        appandEntry(strBuf, tTrieNode->freq);
    }
}

void WordFreq::traversTree(TrieNode* root, int level)
{
    if(!root) return ;
    visitTrieNode(root, level);
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
