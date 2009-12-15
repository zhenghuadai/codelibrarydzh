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
class TrieNode
{
    public:
        size_t freq;
        union{
            char c;
            U32 u32;
        };
        TrieNode* mChild;
        TrieNode* mSib;
    public:
        TrieNode():freq(0),c(0),mChild(0),mSib(0){}
        TrieNode(char tC):freq(0),c(tC),mChild(0),mSib(0){}
        ~TrieNode(){if(mChild) delete mChild; if(mSib) delete mSib;}
    public:
        int add(char* str, int len);
        int add(char* str){add(str, strlen(str));}
        TrieNode* add(char tC);
		int search(char* str, int len);
    private:
        void inc(){freq ++;}
        void addSib(TrieNode* tSib);
        void addChild(char*str, int len);
        void addSibNew(char* str, int len);
        TrieNode* addSibNew(char tC);
        void addChildNew(char* str, int len);
        TrieNode* find(char tC);
};


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
        WordFreq();
        ~WordFreq();
        void start();
        void stat(char* txt);
        void end();
        void print();
        void sort(int key=0);
        void analyse();
    private:
        TrieNode* pHead;
        int words;
        int wordNumTotal;
        Entry *mEntry;
        int mEntrySize;
        int chNum;
        char* strPool;
        int strPoolSize;
        int tEntryIndex;
        char* tPstr;
		int charFreq[256];
    private:
        void appandEntry(const char* str, size_t freq);
        void traversTree(TrieNode* root, int level);
        void visitTrieNode(TrieNode* tTrieNode, int level);
        void destroy();
        void getFreq();
};
