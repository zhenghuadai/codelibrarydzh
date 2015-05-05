#include "common.h"

static vector<void(*)()> tests;
Test::Test(void (*foo)())
{
	tests.push_back(foo);
}

void Test::run()
{
	for(auto item :tests){
		item();
	}
}

int main(int argc, char** argv)
{
	Test::run();	
	return 0;
}
