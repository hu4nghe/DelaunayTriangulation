/**
 * This file is created to realize the point and triangle object some fonctions with them.
 * These objects are used to represent points and triangles in two-dimensional space.
 */
#ifndef _GRAPH_H_
#define _GRAPH_H_

/**
 * Using stdboll.h for bool return value.
 */
#include "stdbool.h"
#include "stdio.h"

typedef struct point
{
    /* data */
    double x, y;
} point;

typedef struct triangle
{
    /* data */
    point a, b, c;
} triangle;

typedef struct edge
{
    /* data */
    point edgePoint1,edgePoint2;
} edge;

typedef struct circle
{
    /* data */
    point centre;
    double radius;
} circle;


void pointInit(point* p,double x, double y);
bool triangleInitThreePoint(triangle* t,point a, point b,point c);
bool triangleInitPointEdge(triangle* t,const point a, const edge e);
bool circleInit(circle* c,point centre,double radius);
bool edgeInit(edge* e, point edgePoint1, point edgePoint2);

void printPoint(FILE* mshOut,const point p,int num);
void printTriangle(FILE* mshOut,const triangle t,int num);

double Distance(const point a, const point b);
double Slope(const point a, const point b);
double surfaceTriangle(const triangle t);
circle circumCircle(const triangle t);

bool isEqualDouble(const double a, const double b);
bool isEqualPoint(const point a, const point b);
bool isEqualEdge(const edge e1,const edge e2);
bool isInCircle(const point p, const circle c);

#endif /* _GRAPH_H_ */