#ifndef _GRAPH_HPP
#define _GRAPH_HPP

#include <cstdlib>
#include <fstream>

using std::fstream;

class point
{
    public :
		point() = default;
        point(double a,double b);
        bool print(fstream mshOut,const point p,unsigned count) const;
        double Distance(const point p) const;
        double Slope(const point p) const;
        bool operator==(const point p) const;
        
    private :
        double x;
        double y;
};

class edge 
{
    public : 
        edge() = default;
        edge(const point a,const point b);
		point getA() const;
		point getB() const;
        bool operator==(const edge e);
    private : 
        point a;
        point b;

};

class circle
{
    public :
        circle() = default;
        circle(point centre,double radius);
        bool includePoint(const point p) const;
    private : 
        double radius;
        point centre;
        
};


class triangle
{
    public:
        triangle() = default;
        triangle(const point a,const point b,const point c);
		triangle(const edge e,const point a);
        double surface(const triangle t) const;
        circle circumCircle(const triangle t) const;
        bool print(fstream out,const triangle t,int count) const;
    private:
        point a;
        point b;
        point c;
};

#endif//Graph.hpp