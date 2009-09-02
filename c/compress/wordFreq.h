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
class Entry 
{
    public:
        const char* str;
        size_t freq;
        Entry(){}
        Entry(const char* s, size_t f){str=s; freq=f;}
        void set(const char* s, size_t f){str=s; freq=f;}
    public:
    static int compareFreq( const void * node1, const void* node2){
        return (((Entry*)node1)-> freq < ((Entry*)node2)->freq ? 1:-1);
    }
};

class WordFreq
{
    public:
        WordFreq():pHead(0),words(0), wordNumTotal(0), mEntry(NULL),mEntrySize(0),chNum(0),strPool(0),strPoolSize(0){}

        ~WordFreq(){destroy(); if (strPool) delete strPool; if(mEntry) delete mEntry;}
        void start();
        void stat(char* txt);
        void end();
        void print();
        void sort(int key=0);
    private:
        Node* pHead;
        int words;
        int wordNumTotal;
        Entry *mEntry;
        int mEntrySize;
        int chNum;
        char* strPool;
        int strPoolSize;
        int tEntryIndex;
        char* tPstr;
    private:
        void appandEntry(const char* str, size_t freq);
        void traversTree(Node* root, int level);
        void visitNode(Node* tNode, int level);
        void destroy();
        void getFreq();

};
