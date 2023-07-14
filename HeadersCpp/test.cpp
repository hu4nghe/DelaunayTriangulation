#include <iostream>
#include "Graph.hpp"

int main()
{
	point a(5.2,3.8);
	point b(8.29,1.4);
	point c(1.4,5.3);
	triangle t(a,b,c);
	
	circle s = t.circumCircle();


	return 0;
}