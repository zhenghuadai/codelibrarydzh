#include "common.h"
#include "utils.h"
#include <fstream>

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

int doTests(string filename,  function<bool(json&)> func)
{
    ifstream in(filename);
    json tests = json::parse(in); 
    cout<<"Test " << filename <<" starts:"<<endl;
    bool rets = true;
    for (auto test: tests) {
        bool result  = func(test);
        if(result == true){
            cout<<".";
        }else{
            cout<<"F";
            rets = false;
        }
    }
    cout<<endl;
    cout<<"Test " << filename <<(rets?" success":" fail")<<endl;
    cout<<endl;
}


int main(int argc, char** argv)
{
	Test::run();	
	return 0;
}
