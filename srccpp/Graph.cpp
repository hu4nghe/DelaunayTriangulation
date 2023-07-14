#include "Graph.hpp"
#include <iostream>

circle triangle::circumCircle() const
{  
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1*a1 + b1*b1)/2;  
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2*a2 + b2*b2)/2;  
    double d = a1 * b2 - a2 * b1;

    point centrePoint(a.x + (c1*b2 - c2*b1)/d,a.y + (a1*c2 - a2*c1)/d);
    circle res(centrePoint, centrePoint.Distance(a));
    return res; 
}

std::ostream& operator<<(std::ostream &mshOut, triangle &t)
{
	const std::string mshEndL = "//+\n";
	std::string outPut = t.a.mshOutputFormat() +  mshEndL
					   + t.b.mshOutputFormat() +  mshEndL
					   + t.c.mshOutputFormat() +  mshEndL;
	
	mshOut<<outPut<<std::endl;

	return mshOut;	
}

std::istream& operator>>(std::istream &in, point &p)
{
	in>>p.x>>p.y;
	return in;
}

int point::pointCount = 0;
/*
int main()
{
	point a,b,c;
	std::cin>>a>>b>>c;
	triangle T(a,b,c);
	std::cout<<T<<std::endl;
	
	return 0;
}
*/