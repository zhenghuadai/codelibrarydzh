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


HuffNode* buildHuffmanTree(size_t* freq)
{

}
inline void insertLink(Link*& head, Link* tLink)
{
    if((! head) ||( !tLink)) return ; 
    Link* pLink = head;
    Link* nLink = head;
    while(nLink && (nLink -> node -> freq < tLink -> node -> freq)){
        pLink = nLink;
        nLink = nLink -> next;
    }
    if(nLink == head){
        tLink -> next = head;
        head = tLink;
    }else{
        pLink -> next = tLink;
        tLink -> next = nLink;
    }

}

inline HuffNode* getMinNode(Link*&  head, int arm)
{
    HuffNode* node = head -> node;
    node -> arm = arm; 
    head = head-> next;
    return node;
}

void SetNodeCode(HuffNode* node)
{
    HuffNode* parent = node->parent;
    node->hCode = node->arm;
    node->len =1;
    while(parent && (parent -> arm !=255))
    {
        node->hCode <<= 1;
        node->hCode |= parent->arm;
        node->len++;
        parent = parent->parent;
    }
}

HuffmanS::HuffmanS(char* txt)
{
}

void printLink(Link* head)
{
    Link* p=head;
    int i=0;
    while(p!=NULL)
    {
        printf("<%d %5d> ", i++, p->node->freq);
        p = p->next;
    }
    printf("\n");
}

void HuffmanS::buildCodeTable(unsigned char* txt)
{
    buildTree(txt);
    for(int i= 0; i< leafCount; i++)
        SetNodeCode(&mNodes[i]);

    for(int i= 0; i< leafCount; i++){
        unsigned char c = mNodes[i].ch;
        codeTable[c] = mNodes[i].hCode;
        codeLen[c] = mNodes[i].len;
        //printf("[%c: %d, %0x], ", c, codeLen[c], codeTable[c]);   
    }
    //printf("\n");

}
void* HuffmanS::buildTree( unsigned char* txt)
{
    leafCount= 0;
    int i;
    getFreq((unsigned char*)txt); 
    hSortFromFrq();

    Link link[256]={0}; 
    Link *linkHead;
    link[0].next =0; link[0].node=&mNodes[0];
    for(i =1; (i< 256) && (mNodes[i].freq>0); i++){
        link[i].node = &mNodes[i];
        link[i].next = &link[i-1];
    }

    linkHead = &link[i-1];
    leafCount = i;
    int curNode = leafCount;
    while(linkHead){
        Link* tLink;
        HuffNode* pNode = &mNodes[curNode++];
        tLink = linkHead;
        pNode -> left = getMinNode(linkHead, armLeft);
        tLink -> next =0; tLink -> node = 0;

        tLink = linkHead;
        pNode -> right= getMinNode(linkHead, armRight);
        pNode -> freq = pNode -> left -> freq + pNode -> right -> freq;
        pNode -> left -> parent = pNode-> right -> parent = pNode;
        tLink -> next =0; tLink -> node = pNode;
        insertLink(linkHead, tLink);
    }
}

void HuffmanS::getFreq(unsigned char* txt)
{
    unsigned char* p= txt;
    for(int i=0;i<256;i++)
        freq[i] =0;
    while(*p) {
        freq[*p++] ++;
    }
}

int cmpLongLong(const void* q1, const void* q2){
    return ( *(unsigned long long* )q1 < *(unsigned long long*) q2 ? 1: -1);
}
void HuffmanS::hSortFromFrq()
{
#if 0
    for(int i=0;i<256;i++){
        mNodes[i].ch = i;
        mNodes[i].freq = freq[i];
    }
    hSort((void*)mNodes);
#else
    int i;
    for(i=0;i<256;i++){
        freq[i] = (freq[i] << 8 ) | i;
    }
    qsort(freq, 256, sizeof(long long ), cmpLongLong);
    for(i=0;i<256;i++){
        unsigned char c = freq[i] & 255;
        mNodes[i].ch = c;
        mNodes[i].freq = freq[i]>> 8;
    }

#endif
}

void HuffmanS::hSort(void* nodes)
{
    qsort(nodes,256, sizeof(HuffNode), HuffNode::compareHuffNode);
}

size_t HuffmanS::code(char* txt, size_t txtLen,  char*ctxt)
{
    reset();
    buildCodeTable((unsigned char*) txt);
    int nDesBitIndex = 0;
    for(int i= 0; i< txtLen; i++)
    {
        *(U32*)(ctxt+(nDesBitIndex>>3)) |= codeTable[txt[i]] << (nDesBitIndex&7);
        nDesBitIndex += codeLen[txt[i]];
    }
    return nDesBitIndex;
}
