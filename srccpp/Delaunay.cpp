#include <algorithm>
#include <iterator>
#include <vector>

#include "Graph.hpp"
#include "Graph.cpp"

triangle superTriangle(std::vector<point> &vecPoint)
{
	double xMax, yMax, xMin, yMin;
	xMax = yMax = xMin = yMin = 0.0;

	for(auto &p : vecPoint)
	{
		xMax = std::max(xMax, p.getX());
		yMax = std::max(yMax, p.getY());
		xMin = std::min(xMin, p.getX());
		yMin = std::min(yMin, p.getY());
	}

	double xAvg = (xMax + xMin) / 2;
	double k = (yMax - yMin) / (xMax - xMin);

	point a(xAvg, k * (xAvg - xMax) + yMax);
	point b(xMax + (yMin - yMax - 1) / k + 1, yMin - 1);
	point c(2 * xAvg - b.getX(), yMin - 1);

	vecPoint.push_back(a);
	vecPoint.push_back(b);
	vecPoint.push_back(c);

	return triangle(a,b,c);

}

void removeDuplicatedEdges(std::vector<edge> &vecEdge)
{
	std::sort(vecEdge.begin(),vecEdge.end());
	vecEdge.erase(std::unique(vecEdge.begin(),vecEdge.end()), vecEdge.end());
}

int main()
{
	std::vector<triangle> vecTriangle;
	std::vector<edge> vecEdge;
	std::vector<point> vecPoint;

	int N = 0;
	std::cin>>N;

	point Input;

	for(int i = 0; i < N;i++)
	{
		std::cin>>Input;
		vecPoint.push_back(Input);
	}

	triangle supTri = superTriangle(vecPoint);
	
	return 0;

}

/*
int main()
{
	std::vector<triangle> vecTriangle;
	std::vector<edge> vecEdge;
	std::vector<point> vecPoint;

	int N = 0;
	std::cin>>N;

	point Input;

	for(int i = 0; i < N;i++)
	{
		std::cin>>Input;
		vecPoint.push_back(Input);
	}

	vecTriangle.push_back(superTriangle(vecPoint));
	for(auto &iterPnt : vecPoint)
	{
		vecEdge.clear();
		for(auto &iterTri : vecTriangle)
		{
			if(iterTri.circumCircle().includePoint(iterPnt))
			{
				
			}
		}

	}



}*/
