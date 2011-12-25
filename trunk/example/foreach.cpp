#!/home/zhdai/bin/dcsh
/*
 * =====================================================================================
 *
 *       Filename:  foreach.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/17/2011 07:10:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "foreach.h"
//using namespace std;
void printElem(int& elem) {
    std::cout << elem << std::endl;
}

#include <stdio.h>
#include <stdlib.h>
int test_file_each(int argc, char** argv)
{

    char* fn ;
    if (argc >1)
        fn = argv[1];
    else
        return 0;
    file_eachline(line in fn, ({
                printf("%s", line);
                }));
    file_eachbyte(ch in fn, ({
                printf("%c", ch);
                }));
}

int test_each(int argc, char** argv)
{
    int ia[] = {1, 2, 3};
    std::string s="hello world";
    std::vector<int> ivec(ia, ia + sizeof(ia) / sizeof(int));
    foreach(a in ivec, ({
                std::cout<< a << std::endl;
                ;}));
    foreach(a in ivec, ({
               a = _m_i; 
                ;}));
    foreach(a in ivec, ({
                std::cout<< a << std::endl;
                ;}));
    for_each(ivec.begin(), ivec.end(), printElem);

    foreach(a in ia, ({
                std::cout<< a << std::endl;
                ;}));

    foreach(a in s, ({
                std::cout<< a<<std::endl;
                ;}));
}

int main(int argc, char** argv)
{
    test_file_each(argc,argv);
    test_each(argc,argv);
}
