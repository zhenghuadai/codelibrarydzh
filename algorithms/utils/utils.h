/*
 * =====================================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/2015 02:16:06 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  utils_algorithm_test_INC
#define  utils_algorithm_test_INC

#include "json.hpp"
using json = nlohmann::json;
int doTests(string filename,  function<bool(json&)> func);

class Test {
public:
	Test(void(*foo)());
	static void run();
};

#define APPEND_TO_TEST() \
	static Test t(test);


namespace DM{
void readBinaryTree(BinaryTree *&p, istream &fin) ;
}
#endif   /* ----- #ifndef utils_algorithm_test_INC  ----- */
