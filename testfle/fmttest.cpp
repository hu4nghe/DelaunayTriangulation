#include <iostream>
#include <string>
#define FMT_HEADER_ONLY
#include "fmt/format.h"
using namespace std;

class test
{
	friend ostream& operator<<(ostream &out,const test &target1);

	public : 
		test() : out("hello,world"), i1(0), i2(0), i3(0) {}

	private : 
		string out;
		int i1;
		int i2;
		int i3;

};

ostream& operator<<(ostream &out,const test &target1)
{
	auto str = fmt::format("a string and  3 interger : {}, {}, {}, {}\n",target1.out, target1.i1, target1.i2, target1.i3);
	out<<str;
	return out;
}

int main()
{
	test test1;
	cout<<test1<<endl;
	return 0;
}