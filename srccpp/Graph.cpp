#include "Graph.hpp"

using std::fstream;

/**
 * implementation of point class
 */

/**
 * @brief Construct a new point::point object
 * 
 * @param a 
 * @param b 
 */
point::point(double a, double b)
{
	x = a;
	y = b;
}

/**
 * @brief print a point object to mshOut file.
 * 
 * @param mshOut file
 * @param p point to print
 * @param count count of point
 * @return true print successed
 * @return false print failed
 */
bool point::print(fstream mshOut,const point p,unsigned count) const
{

}

/**
 * @brief calculate the distance between two points
 * 
 * @param p another point
 * @return double disctance between point himself and p
 */
double point::Distance(const point p) const
{

}

/**
 * @brief calculate the slope between two points
 * 
 * @param p another point
 * @return double the slope between two points
 */
double point::Slope(const point p) const
{

}

bool point::operator==(const point p) const
{
	return (this->x == p.x && this->y == p.y);
}


/**
 * inplementation of class edge
 */

edge::edge(const point x,const point y)
{
	a = x;
	b = y;
}

point edge::getA() const
{
	return a;
}

point edge:: getB() const
{
	return b;
}

bool edge::operator==(const edge e)
{
	return (this->a == a && this->b == b);
}

/**
 * implementation of class circle
 */

/**
 * @brief Construct a new circle::circle object
 * 
 * @param c 
 * @param r 
 */
circle::circle(point c,double r)
{
	centre = c;
	radius = r;
}

bool circle::includePoint(const point p) const
{
	
}

triangle::triangle(const point a,const point b,const point c)
{
	if((a == b) && (b == c) && (c == a))

	this->a = a;
	this->b = b;
	this->c = c;

}

triangle::triangle(const edge e,const point a)
{
	this->a = a;
	this->b = e.getA();
	this->c = e.getB();
}

double triangle::surface(const triangle t) const
{

}

circle triangle::circumCircle(const triangle t) const
{

}

bool triangle::print(fstream out,const triangle t,int count) const
{

}
