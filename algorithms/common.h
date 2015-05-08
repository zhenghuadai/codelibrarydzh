#ifndef  COMMON_ALGORITHM_TEST_INC
#define  COMMON_ALGORITHM_TEST_INC

#include <limits.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
typedef TreeNode BinaryTree;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

#define ClassName0(aa) Solution_ ## aa 
#define ClassName(aa) ClassName0(aa) 
#define Solution ClassName(__FILE_NAME__)
#endif   /* ----- #ifndef COMMON_ALGORITHM_TEST_INC  ----- */
