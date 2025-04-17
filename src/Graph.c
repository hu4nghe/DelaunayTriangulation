#include "Graph.h"
#include "stdbool.h" 
#include "math.h"
/**
 * @brief 
 * A constructor of object point.
 * 
 * @param p The point himself.
 * @param x horizontal coordinate.
 * @param y vertical coordinate.
 */
void pointInit(point* p, double x, double y)
{
    p -> x = x;
    p -> y = y;
}

/**
 * @brief 
 * A constructor of object Triangle by define his 3 vertex.
 * 
 * @param t The triangle himself.
 * @param a A vertex of triangle.
 * @param b A vertex of triangle.
 * @param c A vertex of triangle.
 * @return true if a,b and c are not on the same line.
 *         false if a,b and c are on the same line.
 */
bool triangleInitThreePoint(triangle* t, const point a, const point b, const point c)
{
    t -> a = a;
    t -> b = b;
    t -> c = c;
    if(isEqualDouble(surfaceTriangle(*t), 0.0)) return false;
    else return true;
}

/**
 * @brief 
 * A constructor of object Triangle by define his 3 vertex.
 * 
 * @param t The triangle himself.
 * @param a A vertex of triangle.
 * @param b A vertex of triangle.
 * @param c A vertex of triangle.
 * @return true if a,b and c are not on the same line.
 *         false if a,b and c are on the same line.
 */
bool triangleInitPointEdge(triangle* t,const point a, const edge e)
{ 
    t -> a = a;
    t -> b = e.edgePoint1;
    t -> c = e.edgePoint2;
    if(isEqualDouble(surfaceTriangle(*t), 0.0)) return false;
    else return true;
}

/**
 * @brief 
 * A constructor of object circle.
 * 
 * @param c The circle himself.
 * @param centre the centre of this circle.
 * @param radius the radius of this circle.
 * @return true if radius is not 0.
 *         false if radius is 0.
 */
bool circleInit(circle* c,point centre,double radius)
{
    if(radius)
    {
        c->centre = centre;
        c->radius = radius;
        return true;
    }
    else return false;
}

/**
 * @brief 
 * A constructor of object edge
 * 
 * @param edge himself
 * @param edgepoint1 a point
 * @param edgepoint2 a point
 * 
 * @return true if two points are not the same point, false if they are.
 * 
 */
bool edgeInit(edge* e, point edgePoint1, point edgePoint2)
{
    if(isEqualPoint(edgePoint1, edgePoint2))
        return false;
    else
    {
        e->edgePoint1 = edgePoint1;
        e->edgePoint2 = edgePoint2;
        return true;
    }
}

/**
 * @brief 
 * Printing a point in .geo format
 * 
 * @param mshOut *FILE output 
 * @param p the point to print
 * @param num printed point count
 */
void printPoint(FILE* mshOut, const point p, int num)
{
    fprintf(mshOut, "Point (%d) = {%f,%f,0};\n", num, p.x,p.y);
}

/**
 * @brief 
 * Printing a triangle in .geo format
 * 
 * @param mshOut *FILE output 
 * @param t the triangle to print
 * @param num printed point count
 */
void printTriangle(FILE* mshOut, const triangle t, const int num)
{
    printPoint(mshOut,t.a,3 * num - 2);
    fprintf(mshOut,"//+\n");
    printPoint(mshOut,t.b,3 * num - 1);
    fprintf(mshOut,"//+\n");
    printPoint(mshOut,t.c,3 * num);
    fprintf(mshOut,"//+\n");

    fprintf(mshOut, "Line(%d) = {%d,%d};\n",3 * num - 2, 3 * num - 2, 3 * num - 1);
    fprintf(mshOut, "//+\n");
    fprintf(mshOut, "Line(%d) = {%d,%d};\n",3 * num - 1, 3 * num - 1, 3 * num);
    fprintf(mshOut, "//+\n");
    fprintf(mshOut, "Line(%d) = {%d,%d};\n",3 * num    , 3 * num - 2, 3 * num);
    fprintf(mshOut, "//+\n");
}

/**
 * @brief
 * Distance between two points in the plane.
 * 
 * @param a the first point.
 * @param b the second point.
 * @return the distance between a and b.
 */
double Distance(const point a, const point b)
{
    return sqrt(pow((a.x - b.x), 2.0) +
                pow((a.y - b.y), 2.0));
}

/**
 * @brief
 * Slope between two points in the plane.
 * 
 * @param a the first point.
 * @param b the second point.
 * @return the slope between a and b.
 */
double Slope(const point a, const point b)
{
    return ((a.y - b.y) / (a.x - b.x));
}

/**
 * @brief
 * Calculate the surface of a triangle.
 * 
 * using determinant to calculate,might have precision loss.
 * @param t a triangle object.
 * @return the surface of this triangle.
 */
double surfaceTriangle(const triangle t)
{
    return 0.5*((t.b.x * t.c.y - t.c.x * t.b.y) - 
                (t.a.x * t.c.y - t.c.x * t.a.y) + 
                (t.a.x * t.b.y - t.b.x * t.a.y));
}

/**
 * @brief
 * this fonction accept a triagle and calculate his circumCircle by formula.
 * 
 * @param t the triagle that we want to use.
 * @return the circumCircle of t. 
 */
circle circumCircle(const triangle t)
{  
    double a1 = t.b.x - t.a.x, 
           b1 = t.b.y - t.a.y, 
           c1 = (a1 * a1 + b1 * b1) / 2;  
    double a2 = t.c.x - t.a.x, 
           b2 = t.c.y - t.a.y, 
           c2 = (a2 * a2 + b2 * b2) / 2;  

    double d  = a1 * b2 - a2 * b1;

    point centre;
    pointInit(&centre,
              t.a.x + (c1 * b2 - c2 * b1) / d,
              t.a.y + (a1 * c2 - a2 * c1) / d);  
  
    circle c;
    circleInit(&c,
                centre,
                Distance(centre, t.a));
    return c; 
}

/**
 * @brief
 * This fonction do comparison between two double numbers.
 * 
 * __DBL_EPSILON__ is used to prevent the problems due to the precision loss.
 * @param a a number.
 * @param b an another number.
 * @return true if they are approximatly equal. false if they are not.
 */
bool isEqualDouble(const double a, const double b)
{
    return fabs(a - b) < DBL_EPSILON ? true : false; 
}

/**
 * This fonction check if two points are the same.
 * 
 * @param a a point.
 * @param b an another point.
 * @return True if they are the same point. false if they are not.
 */
bool isEqualPoint(const point a, const point b)
{
    return (a.x == b.x && a.y == b.y) ? true : false;
}

/**
 * This fonction check if two edge are the same.
 * 
 * @param e1 an edge.
 * @param e2 an another edge.
 * @return True if they are the same edge. false if they are not.
 */
bool isEqualEdge(const edge e1,const edge e2)
{
    return ((isEqualPoint(e1.edgePoint1, e2.edgePoint1)  &&
             isEqualPoint(e1.edgePoint2, e2.edgePoint2)) ||
            (isEqualPoint(e1.edgePoint1, e2.edgePoint2)  &&
             isEqualPoint(e1.edgePoint2, e2.edgePoint1)));
}


/**
 * This fonction check if a point is inside a circle.
 * 
 * @param p the point that we want to check.
 * @param c the circle that we want to check.
 * @return True if the point is inside the circle. false if it is not.
 */
bool isInCircle(const point p, const circle c)
{
    if(Distance(p, c.centre) <= c. radius)
        return true;
    else
        return false;
}