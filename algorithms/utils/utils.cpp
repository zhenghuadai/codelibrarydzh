#include "common.h"

namespace DM{
//http://articles.leetcode.com/2010/09/serializationdeserialization-of-binary.html
void writeBinaryTree(BinaryTree *p, ostream &out) {
    if (!p) {
        out << "# ";
    } else {
        out << p->val << " ";
        writeBinaryTree(p->left, out);
        writeBinaryTree(p->right, out);
    }
}

enum TokenType{
    TOKEN_NONE = 0,
    TOKEN_$ = 1,
    TOKEN_NUM = 2
};

static TokenType readNextToken(int& token, istream& fin)
{
    char c; 
    TokenType t = TOKEN_NONE;
    int num = 0;
    while( (!fin.eof()) &&((c = fin.get())==' ')){
    }
    if( c == '#'){
        fin.get();
        t = TOKEN_$ ;
    }else if ( c >='0' && c<='9'){
        num = c - '0';
        while( (!fin.eof())){
            c = fin.get();
            if(c >='0' && c<='9'){
                num = num * 10 + (c - '0');
            }else{
                token = num;
                t = TOKEN_NUM;
                break;
            }
        }
    }else{

    }
    return t;
}

void readBinaryTree(BinaryTree *&p, istream &fin) {
    int token;
    bool isNumber;
    TokenType t = readNextToken(token, fin);
    if (t == TOKEN_NUM) {
        p = new BinaryTree(token);
        readBinaryTree(p->left, fin);
        readBinaryTree(p->right, fin);
    }
}

}
