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
    Link* pLink = head;
    Link* nLink = head;
    while(nLink && (nLink -> node -> freq < tLink -> node -> freq)){
        nLink = nLink -> next;
        pLink = nLink;
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
    while(parent )
    {
        node->hCode <<= 1;
        node->hCode |= parent->hCode;
        node->len++;
        parent = parent->parent;
    }
}

void* HuffmanS::buildTree( unsigned char* txt)
{
    int leafCount= 0;
    int i;
    getFreq((unsigned char*)txt); 
    for(i=0;i<256;i++){
        mNodes[i].ch = i;
        mNodes[i].freq = freq[i];
    }
    hSort((void*)mNodes);

    Link link[256]; 
    Link *linkHead;
    link[0].next =0; link[0].node=&mNodes[0];
    for(i =0; i< 256 && mNodes[i].freq; i++){
        link[i].node = &mNodes[i];
        link[i].next = &link[i-1];
    }

    linkHead = &link[i-1];
    leafCount = i;
    int curNode = leafCount;
    while(linkHead){
        Link* tLink;
        HuffNode* pNode = &mNodes[curNode++];
        pNode -> left = getMinNode(linkHead, armLeft);
        tLink = linkHead;
        pNode -> right= getMinNode(linkHead, armRight);
        pNode -> freq = pNode -> left -> freq + pNode -> right -> freq;
        pNode -> left -> parent = pNode-> right -> parent = pNode;
        tLink -> next =0; tLink -> node = pNode;
        insertLink(linkHead, tLink);
    }
    for(int i= 0; i< leafCount; i++)
        SetNodeCode(&mNodes[i]);



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

void HuffmanS::hSort(void* nodes)
{
    qsort(nodes,256, sizeof(HuffNode), HuffNode::compareHuffNode);
}
