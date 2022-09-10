#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

/**
 * this is the api of the algorithme "triagulation de delaunay"
 */

#include "List.h"  /*which includes stdlib.h*/
#include "Graph.h"/*which includes stdbool.h*/

/**
 * inplementation of list using macro
 * type : point, triangle and edge.
 */

List_IMPL(point);
List_IMPL(triangle);
List_IMPL(edge);

/**
 * this fonction accept a point set, calculate a super triangle who includes all the points in this set.
 * It also adds the vertices of this super triangle into the point set.
 * 
 * @param listPoint the set of points
 * @return a super triangle who includes all the points in listPoint. 
 */
triangle superTriangle(List_point_* listPoint);

/** 
  * This function will remove all duplicated edges in the list.
  * 
  * @param list the edge list that we want to operate. 
  */
void removeDuplicatedEdges(List_edge_* listEdge);

/** 
  * This function will add a triangle's three edge into a edge list.
  * 
  * @param t the triangle that we want to add.
  * @param listEdge the edge list that we want to operate. 
  */
void pushTriangleEdges(const triangle t, List_edge_* listEdge);

/**
 * this fonction check if a triangle use one of the vertex of the supertriangle.
 * @param t the triangle that we want to check.
 * @return true if it use one of the vertex of the supertriangle. false if it do not.
*/
bool usingSuperTriangle(const triangle t);

/**
 * algorithm it self.
 */
int delaunay();

#endif
