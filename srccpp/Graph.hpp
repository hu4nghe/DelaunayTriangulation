#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#define FMT_HEADER_ONLY

#include <fstream>
#include <cmath>
#include <string>
#include "fmt/format.h"

using std::fstream;

class point
{
	friend class triangle;
	friend std::istream& operator>>(std::istream &in, point &p); 

    public :
		point() = default;
        point(const double &abscissa,const double &ordinate) : x(abscissa), y(ordinate) {}
		double getX() {return x;}
		double getY() {return y;}
        double Distance(const point &p) const {return sqrt(pow((x-p.x),2.0)+pow((y-p.y),2.0));}
        bool operator==(const point &p) const {return (x == p.x && y == p.y);};
		std::string mshOutputFormat() { return fmt::format("Point ({}) = {{{},{},0}};\n",pointCount, x, y);}
		static int pointCount;
	     
	private :
        double x;
        double y;
};

class edge
{
    public :
        edge() = default;
        edge(const point &pointA,const point &pointB) : a(pointA), b(pointB) {}
		point getA() const {return a;}
		point getB() const {return b;}
        bool operator==(const edge &e) const {return ((a == e.a && b == e.b)||(a == e.b && b == e.a));}
    private : 
        point a;
        point b;

};

class circle
{
    public :
        circle() = default;
        circle(const point &centre,const double &radius) : r(radius), c(centre) {}
        bool includePoint(const point &p) const {return (p.Distance(c) <= r);}
    private : 
        double r;
        point c;
        
};


class triangle
{
	friend std::ostream& operator<<(std::ostream &mshOut, triangle &t);
	friend class point;

    public:
        triangle() = default;
        triangle(const point &pointA,const point &pointB,const point &pointC) : a(pointA), b(pointB), c(pointC) {}
		triangle(const edge e,const point pointA) : a(pointA), b(e.getA()), c(e.getB()) {}
        double surface(const triangle &t) const { return 0.5*((t.b.x*t.c.y-t.c.x*t.b.y)-(t.a.x*t.c.y-t.c.x*t.a.y)+(t.a.x*t.b.y-t.b.x*t.a.y));}
        circle circumCircle() const;
    private:
        point a;
        point b;
        point c;
};

#endif//Graph.hpp