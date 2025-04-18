/**
 * @file Delaunay.h
 * @author HUANG He (he.huang@utt.fr)
 * @brief
 * This is the algorithm part of the project NF06 "triangulation de Delaunay".
 * Using Bowyer-Watson algorithm.
 * @version 1.0
 * @date 2022-12-20
 * 
 */

/* Macro list definition */
#include "List.h"  

/* Definition of graphics : point, line, triangle, cercle. */
#include "Graph.h"

/**
 * inplementation of list using macro
 * type : point, triangle and edge.
 */

List_IMPL(point);
List_IMPL(triangle);
List_IMPL(edge);

/**
 * * @brief
 * this fonction accept a point set, calculate a super triangle who includes all the points in this set.
 * It also adds the vertices of this super triangle into the point set.
 * 
 * @param listPoint the set of points
 * @return a super triangle who includes all the points in listPoint. 
 */
triangle superTriangle(List_point_* listPoint);

/** 
 * * @brief
  * This function will remove all duplicated edges in the list.
  * 
  * @param list the edge list that we want to operate. 
  */
void removeDuplicatedEdges(List_edge_* listEdge);

/** 
 * * @brief
  * This function will add a triangle's three edge into a edge list.
  * 
  * @param t the triangle that we want to add.
  * @param listEdge the edge list that we want to operate. 
  */
void pushTriangleEdges(const triangle t, List_edge_* listEdge);

/**
 * * @brief
 * this fonction check if a triangle use one of the vertex of the supertriangle.
 * 
 * @param t the triangle that we want to check.
 * @return true if it use one of the vertex of the supertriangle. false if it do not.
*/
bool usingSuperTriangle(const triangle t);