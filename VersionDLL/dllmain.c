/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>

/**
 * this is the algorithm part of the project NF06 "triangulation de delaunay".
 * using algorithm of Bowyer-Watson.
 * by HUANG He,TC04.
 */

#include "Graph.c" /*which includes math.h and stdio.h*/

/**
 * Define three vertices of the super triangle.
 * which are used in the function "superTriangle" and "main".
 */
point a,b,c;

DLLIMPORT point inputPoint()
{
    point p;
    scanf("%lf%lf",&(p.x),&(p.y));
    return p;
}

/**
 * this fonction accept a point set, calculate a super triangle who includes all the points in this set.
 * It also adds the vertices of this super triangle into the point set.
 * 
 * @param listPoint the set of points
 * @return a super triangle who includes all the points in listPoint. 
 */
DLLIMPORT triangle superTriangle(List_point_* listPoint)
{
    double xMax = 0.0, yMax = 0.0, xMin = 0.0, yMin = 0.0;

    List_point_Node* iter = listPoint->head;
    while(iter != NULL)
    {
        if(xMax <= iter->data.x)
            xMax = iter->data.x;
        else if(xMin >= iter->data.x)
            xMin = iter->data.x;

        if(yMax <= iter->data.y)
            yMax = iter->data.y;
        else if(yMin >= iter->data.y)
            yMin = iter->data.y;
        
        iter = iter->next;
    }
    double xAvg = (xMax + xMin) / 2;

    point p1,p2;
    pointInit(&p1,xAvg,yMax);
    pointInit(&p2,xMax,yMin);

    double k = Slope(p1,p2);
    pointInit(&a,xAvg, k * (xAvg - xMax) + yMax);
    pointInit(&b,xMax + (yMin - yMax - 1) / k + 1, yMin - 1);
    pointInit(&c,2 * xAvg - b.x, yMin - 1);
    
    triangle SuperTri;
    triangleInitThreePoint(&SuperTri,a,b,c);
    List_point_push_back(listPoint,a);
    List_point_push_back(listPoint,b);
    List_point_push_back(listPoint,c);

    return SuperTri;
}

 /** 
  * This function will remove all duplicated edges in the list.
  * 
  * @param list the edge list that we want to operate. 
  */
DLLIMPORT void removeDuplicatedEdges(List_edge_* listEdge)
{
    bool duplicated = false;
    /* check if it is a empty list. */
    if(listEdge->tail == NULL)
        return;
    List_edge_Node* iterEdge1 = listEdge->head;
    while(iterEdge1 != NULL)
	{
        duplicated = false;
        List_edge_Node* iterEdge2 = iterEdge1->next;
		while(iterEdge2 != NULL)
		{
			if(isEqualEdge(iterEdge1->data,iterEdge2->data))
			{
                //List_edge_Node* tempIter = iterEdge2->next;
				List_edge_erase(listEdge,&iterEdge2);
                //iterEdge2 = tempIter;
                duplicated = true;
			}
			else
				iterEdge2 = iterEdge2->next;
                
		}
        if(duplicated == true)
        {
            List_edge_erase(listEdge,&iterEdge1);
        }
        else
            iterEdge1 = iterEdge1->next;
        
    }
    return;
}

 /** 
  * This function will add a triangle's three edge into a edge list.
  * 
  * @param t the triangle that we want to add.
  * @param listEdge the edge list that we want to operate. 
  */
DLLIMPORT void pushTriangleEdges(const triangle t, List_edge_* listEdge)
{
    edge A,B,C;//to present 3 edge of a triangle in the listTriangle*
    edgeInit(&A,t.a,t.b);
    edgeInit(&B,t.b,t.c);
    edgeInit(&C,t.c,t.a);
    List_edge_push_back(listEdge,A);
    List_edge_push_back(listEdge,B);
    List_edge_push_back(listEdge,C);
    return;
}

/**
 * this fonction check if a triangle use one of the vertex of the supertriangle.
 * @param t the triangle that we want to check.
 * @return true if it use one of the vertex of the supertriangle. false if it do not.
*/
DLLIMPORT bool usingSuperTriangle(const triangle t)
{
    if(isEqualPoint(t.a,a) || isEqualPoint(t.a,b) || isEqualPoint(t.a,c))
        return true;
	else if(isEqualPoint(t.b,a) || isEqualPoint(t.b,b) || isEqualPoint(t.b,c))
		return true;
	else if(isEqualPoint(t.c,a) || isEqualPoint(t.c,b) || isEqualPoint(t.c,c))
		return true;
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DLLIMPORT int delaunay()
{
    /* start of input*/

    /*Scan the number of points.*/
    int N = 0;
    scanf("%d",&N);

    /*create the listPoint with first scaned element.*/
    List(List_point_,listPoint,inputPoint());

    /*Do N-1 times scan because we have already scan once when creating the listPoint.*/
    for(int i = 1; i < N; i++)
    {
        List_point_push_back(&listPoint,inputPoint());
    }
    
    /* end of input*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*Optimization in the case that there are only 3 points.*/

    if(N == 3)
    {
        FILE * mshOut = fopen("delaunay.geo","w");

        triangle t;
        triangleInitThreePoint(&t,listPoint.head->data,listPoint.head->next->data,listPoint.head->next->next->data);
        
        printTriangle(mshOut,t,1);

        fclose(mshOut);

        return 0;
    }
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    /* start of the algorithm */
    
    /*Calculate the super triangle, and stock it into the triangle list.*/
    List(List_triangle_,listTriangle,superTriangle(&listPoint));

    /* Create a iterator of the listPoint and listTriangle. */
    List_point_Node* iterPoint = listPoint.head;
    List_triangle_Node* iterTriangle = listTriangle.head;

    /* iterate every point in the point set. */
    while(iterPoint != NULL)
    {
        /* initialize listEdge. */
        ListEmpty(List_edge_,listEdge);

        /**
         * check every triangle in the list to check if it is a delaunay triangle.
         * while iter != end and list is not empty.
         */
        iterTriangle = listTriangle.head;
        while(iterTriangle != NULL && listTriangle.tail != NULL)
        {
            if(isInCircle(iterPoint->data, circumCircle(iterTriangle->data)))
            /* the point is inside the circumcircle of this triangle, so it is not a delaunay triangle. */
            {
                /* push all the edges of this triangle into the listEdge. */
                pushTriangleEdges(iterTriangle->data,&listEdge);

                /* remove this triangle from the list. */
                List_triangle_erase(&listTriangle,&iterTriangle);
            }
            else
                iterTriangle = iterTriangle->next;
        }

        /* remove duplicated edges. */
        removeDuplicatedEdges(&listEdge);

        /* create a iterator of listEdge. */
        List_edge_Node* iterEdge = listEdge.head;

        /**
         *  create new trangles with the current point and edges in the listEdge. 
         *  while iter != end and listEdge is not empty.
         */
		while(iterEdge != NULL && listEdge.tail != NULL)
		{
            triangle newFormedTriangle;
            triangleInitPointEdge(&newFormedTriangle,iterPoint->data,iterEdge->data);
            List_triangle_push_back(&listTriangle,newFormedTriangle);
            iterEdge = iterEdge->next;
		}

        /*clear the listEdge for next round use.*/
        List_edge_clear(&listEdge);

        iterPoint = iterPoint->next;
    }
    
    /*remove all the triangles that use the vertex of supertriangle in the list.*/
    
    iterTriangle = listTriangle.head;
    while(iterTriangle != NULL)
	{
	    if(usingSuperTriangle(iterTriangle->data))
        /* if a node in the list is erased, the iterator will point at the next node automatically. */
            List_triangle_erase(&listTriangle,&iterTriangle);
        else
            iterTriangle = iterTriangle->next;
	}
    

/* end of the algorithm */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* start of output*/

    FILE * mshOut = fopen("delaunay.geo","w");

    iterTriangle = listTriangle.head;
    int count = 1;
    while(iterTriangle != NULL && listTriangle.tail != NULL)
    {
        printTriangle(mshOut,iterTriangle->data,count);
        count ++;
        iterTriangle = iterTriangle->next;
    }

    fclose(mshOut);

/* end of output*/
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}
	
	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
