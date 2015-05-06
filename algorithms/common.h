#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Test {
public:
	Test(void(*foo)());
	static void run();
};

#define APPEND_TO_TEST() \
	static Test t(test);

int doTests(string filename,  function<bool(json&)> func);
